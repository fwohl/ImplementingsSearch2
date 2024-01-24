#include <divsufsort.h>
#include <sstream>

#include <seqan3/alphabet/nucleotide/dna5.hpp>
#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/fm_index/fm_index.hpp>
#include <seqan3/search/search.hpp>

int main(int argc, char const* const* argv) {
    seqan3::argument_parser parser{"suffixarray_search", argc, argv, seqan3::update_notifications::off};

    parser.info.author = "SeqAn-Team";
    parser.info.version = "1.0.0";

    auto reference_file = std::filesystem::path{};
    parser.add_option(reference_file, '\0', "reference", "path to the reference file");

    auto query_file = std::filesystem::path{};
    parser.add_option(query_file, '\0', "query", "path to the query file");

    auto number_of_queries = size_t{100};
    parser.add_option(number_of_queries, '\0', "query_ct", "number of query, if not enough queries, these will be duplicated");

    try {
         parser.parse();
    } catch (seqan3::argument_parser_error const& ext) {
        seqan3::debug_stream << "Parsing error. " << ext.what() << "\n";
        return EXIT_FAILURE;
    }

    // loading our files
    auto reference_stream = seqan3::sequence_file_input{reference_file};
    auto query_stream     = seqan3::sequence_file_input{query_file};

    // read reference into memory
    // Attention: we are concatenating all sequences into one big combined sequence
    //            this is done to simplify the implementation of suffix_arrays
    std::vector<seqan3::dna5> reference;
    for (auto& record : reference_stream) {
        auto r = record.sequence();
        reference.insert(reference.end(), r.begin(), r.end());
    }

    // read query into memory
    std::vector<std::vector<seqan3::dna5>> queries;
    for (auto& record : query_stream) {
        queries.push_back(record.sequence());
    }

    // duplicate input until its large enough
    while (queries.size() < number_of_queries) {
        auto old_count = queries.size();
        queries.resize(2 * old_count);
        std::copy_n(queries.begin(), old_count, queries.begin() + old_count);
    }
    queries.resize(number_of_queries); // will reduce the amount of searches

    // Array that should hold the future suffix array
    std::vector<saidx_t> suffixarray;
    suffixarray.resize(reference.size()); // resizing the array, so it can hold the complete SA

    int *SA = (int *)malloc(reference.size() * sizeof(int));
    divsufsort(reinterpret_cast<sauchar_t const*>(reference.data()), SA, reference.size());
    
   // for(int i = 0; i < reference.size(); ++i) {
     //   printf("SA[%2d] = %2d: ", i, SA[i]);
        //for(j = SA[i]; j < n; ++j) {
          //  printf("%c", Text[j]);
        //}
       // printf("$\n");
    //}   
   
    printf("yay");                                 
    //divsufsort(reinterpret_cast<sauchar_t const*>(reference.data()), saidx_t* & suffixarray, reference.size()); 
    //!ImplementMe implement suffix array sort
    //Hint, if can use libdivsufsort (already integrated in this repo)
    //      https://github.com/y-256/libdivsufsort
    //      To make the `reference` compatible with libdivsufsort you can simply
    //      cast it by calling:
    //      `sauchar_t const* str = reinterpret_cast<sauchar_t const*>(reference.data());`
    
    for (auto& q : queries) {
    
    	int m = q.size();  // get length of pattern, needed for strncmp()
    	int n = reference.size();
    	std::cout<<m<<n<<std::endl;
	//printf(char(m));
    // Do simple binary search for the pat in txt using the
    // built suffix array
    	int l = 0, r = n-1;  // Initialize left and right indexes
    	while (l <= r)
    	{
        // See if 'pat' is prefix of middle suffix in suffix array
        	int mid = l + (r - l)/2;
	
		int res=0; 
		std::vector<seqan3::dna5> ref2(reference.begin()+SA[mid],reference.begin()+SA[mid]+m);
		std::cout<<"length"<<ref2.size()<<std::endl;
	//	std::vector<char> ref3;
		//for (auto j : ref2)
		//	std::cout<<j<<std::endl;
	//		ref3.push_back(char(j));
		int res4=0;
		for (int i=0; i<q.size(); i++){
			if (ref2[i] > q[i])
				res4-=1;
				break;
			if (ref2[i] < q[i])
				res4+=1;
				break;
		}
    		//auto fooswoos = std::views::zip(ref2,q);
		//for(auto [foo, woo] : fooswoos) {
     			//woo += foo;
		//	if(foo<woo)
		//		res4-=1;
		//		break;
		//	if(foo<woo)
		//		res4+=1;
		//		break;	
  			
	//	}		//std::cout << i.get<0>() << ' ' << i.get<1>() << ' ';		//std::vector<char> q4(q.begin(),q.end());
		std::cout<<res4<<std::endl;
	//	int res2= strncmp(ref3,ref3,m);
		//seqan3::dna5
	//std::cout<<q[5];
		//printf(ref2);
		//int l = 0;
		//if (ref2 == q)
		//	res=0;
		//if (ref2 != q)
		//	res=1;
	//	for (auto vec3 : q) {
	//	std::cout<<ref2;
	//		l+=1;
		//if (q[i]!=reference[SA[mid]+i]):
		//	res+=1
	//	}	 
	//int res = strncmp(qq, reference[SA[mid]], m);
 
        // If match found at the middle, print it and return
        	if (res == 0)
        	{
			std::cout << "Pattern found at index " << SA[mid]<< std::endl;

		for (auto & element: ref2)
			std::cout<<element.to_char()<<std::endl;
    
        	}
 
        // Move to left half if pattern is alphabetically less than
        // the mid suffix
        	if (res < 0) r = mid - 1;
 
        // Otherwise move to right half
        	else l = mid + 1;
	} 
 	
	
	    //!TODO !ImplementMe apply binary search and find q  in reference using binary search on `suffixarray`
        // You can choose if you want to use binary search based on "naive approach", "mlr-trick", "lcp"
    }

    
}
