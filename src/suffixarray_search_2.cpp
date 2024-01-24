#include <divsufsort.h>
#include <sstream>

#include <seqan3/alphabet/nucleotide/dna5.hpp>
#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/fm_index/fm_index.hpp>
#include <seqan3/search/search.hpp>

void print_vec(std::vector<char> & vecpoint, int first, int last) {
                for (int i=0; i<(last-first);i++)
                        std::cout<< vecpoint[i];
                std::cout<<std::endl;
        }


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
    
    
    //printf("yay");                                 
    //divsufsort(reinterpret_cast<sauchar_t const*>(reference.data()), saidx_t* & suffixarray, reference.size()); 
    //!ImplementMe implement suffix array sort
    //Hint, if can use libdivsufsort (already integrated in this repo)
    //      https://github.com/y-256/libdivsufsort
    //      To make the `reference` compatible with libdivsufsort you can simply
    //      cast it by calling:
    //      `sauchar_t const* str = reinterpret_cast<sauchar_t const*>(reference.data());`
    
    std::vector<char> T;
    for (int i=0; i<reference.size(); i++)
	    T.push_back(reference[i].to_char());

    for (auto& q : queries) {
    
    	int m = q.size();  // get length of pattern, needed for strncmp()
    	int n = reference.size();
	std::vector<char> q_char;
	for (int i=0; i<m; i++)
		q_char.push_back(q[i].to_char());

    // Do simple binary search for the pat in txt using the
    // built suffix array
    //
    // left search
    //
    
	
	int LP;
	int l=0;
	int r=n-1;
	int M;
	if (q_char<=std::vector<char> (T.begin()+SA[0],T.end())){
		std::cout<<"guck hier";
		print_vec(q_char,0,m);
		print_vec(T,SA[0],SA[0]+m+1);
		std::cout<<std::endl;
			//strcmp((q_char.begin(),q_char.end()).c_str(),(T.begin()+SA[0],T.end() ).c_str())<0) {
				//std::string( std::vector<char> (T.begin()+SA[0],T.end())) )<=0 ) {
			//q_char<=std::vector<char> (T.begin()+SA[0],T.end()))))){
		LP=0;
    	}	
	else if ( q_char>std::vector<char> (T.begin()+SA[n],T.end())){
			std::cout<<"guck  hier";
			print_vec(q_char,0,m);
			print_vec(T,SA[n],SA[n]+m+1);

			//strcmp(std::string::c_str(q_char.begin(),q_char.end()),std::string::c_str(q_char.begin(),q_char.end()))<0){
				
				//std::string(std::vector<char> (T.begin()+SA[n],T.end())) ) >0) {
			//q_char> std::vector<char>(T.begin()+SA[n],T.end())) {
		LP=n;
	}
    	else{	
		while(r-l>1){
			M=std::ceil((l+r)/2.0);
			std::cout<<M;
			if ( std::lexicographical_compare(q.begin(), q.end(),
                                                reference.begin() + SA[M],reference.begin() + SA[M] + m)) {

					
					// q_char<=std::vector<char> (T.begin()+SA[M],T.end())){
				std::cout<<"guck hier  :";
				print_vec(q_char,0,m);
				print_vec(T,SA[M],SA[M]+m+1);
					//strcmp(std::string::c_str(q_char.begin(),q_char.end()),std::string::c_str(q_char.begin(),q_char.end()))<0){
						//std::string(std::vector<char> (T.begin()+SA[M],T.end())))>=0 ){
					//q_char<=std::vector<char>(T.begin()+SA[M],T.end())){
				r=M;
			}	
			else{
				std::cout<<"greater";
				print_vec(q_char,0,m);
				print_vec(T,SA[M],SA[M]+m+1);
				l=M;
			}
		}
		LP=r;
	}

	std::cout<<"LP: " << LP<<"suffix: " ;
	print_vec(T,SA[LP],SA[LP]+m);
	print_vec(q_char,0,m);
	int RP;
	l=0;
	r =n-1;
	M;
	if (q_char<std::vector<char>(T.begin()+SA[0],T.begin()+SA[0]+m)){
		RP=0;
	}
	else if(q_char>=std::vector<char>(T.begin()+SA[n],T.begin()+SA[n]+m)){
		RP=n;
		//std::cout<<"why?";
		for (int i=0;i<m;i++) {
			std::cout<<T[SA[n]+i];
		}
		std::cout<<std::endl;
		
		for (int i=0;i<m;i++) {
			std::cout<<q_char[i];
		}
		std::cout<<std::endl;
		//std::cout<<"why?";
		
	}
	else{ while(r-l>1) {
		M=std::ceil((l+r)/2);
		//if(q_char<std::vector<char>(T.begin()+SA[M],T.begin()+SA[M]+m) ){
		//	r=M;
		//}
		//else {
		//	l=M;
		//}
		//
		if(q_char==std::vector<char>(T.begin()+SA[M],T.begin()+SA[M]+m)) {
			l=M;	
			}
		else{
			r=M;
		}

	}

	}
	std::cout<<"RP: "<<RP<<"suffix: ";
	print_vec(T,SA[RP],SA[RP]+m);
	print_vec(q_char,0,m);
	if (LP<=RP){
		std::cout<<"Pattern found " << RP-LP <<"times at positions";
			//for (int i=0; i<RP-LP; i++) {
			//	std::cout<<SA[LP+i];
			//}
			std::cout<<std::endl;

	}
	
	l=0;
	r=n-1;
	while (l <= r)
    	{
        // See if 'pat' is prefix of middle suffix in suffix array
        	int mid = l + (r - l)/2; 
		std::vector<seqan3::dna5> ref2(reference.begin()+SA[mid],reference.begin()+SA[mid]+m);
		//std::cout<<SA[mid]<<std::endl;
		int res4=0;
		for (int i=0; i<q.size(); i++){
			if (reference[SA[mid]+i].to_char() > q[i].to_char()){
				//std::cout<<q[i].to_char() <<"is smaller than" << reference[SA[mid]+i].to_char()<<std::endl;
				res4-=1;//R=M
				break;}
			if (reference[SA[mid]+i].to_char()< q[i].to_char()){
				res4+=1;
				//std::cout<<q[i].to_char() <<"is larger than"<<reference[SA[mid]+i].to_char()<<std::endl;
				break;
			}
		}

		//std::cout<<res4<<std::endl;

        	if (res4 == 0)
        	{
			std::cout << "Pattern found at index " << SA[mid]<< std::endl;
		
		for (auto & element: ref2)
			std::cout<<element.to_char();
    
		for (auto & element: q)
			std::cout<<element.to_char();
        	}


 
        // Move to left half if pattern is alphabetically less than
        // the mid suffix
        	if (res4 < 0) r = mid - 1;
 
        // Otherwise move to right half
        	else l = mid + 1;
	} 
 	
	
	    //!TODO !ImplementMe apply binary search and find q  in reference using binary search on `suffixarray`
        // You can choose if you want to use binary search based on "naive approach", "mlr-trick", "lcp"
    }

    
}
