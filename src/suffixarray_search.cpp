#include <divsufsort.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <seqan3/alphabet/nucleotide/dna5.hpp>
#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/fm_index/fm_index.hpp>
#include <seqan3/search/search.hpp>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
#include <sys/resource.h>
void print_vec(std::vector<char> * vecpoint, int first, int last) {
                for (int i=0; i<(last-first);i++)
                        std::cout<< & vecpoint[i];
                std::cout<<std::endl;
        }

                                  //q_char<=std::vector<char> (T.begin()+SA[0],T.end()))))){
                        //q_char<=std::vector<char> (T.begin()+SA[0],T.end()))))){


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
	std::cout<<"legth:"<<r.size()<<std::endl;
        reference.insert(reference.end(), r.begin(), r.end());
    }

    // read query into memory
    std::vector<std::vector<seqan3::dna5>> queries;
    for (auto& record : query_stream) {
        queries.push_back(record.sequence());
    }
    std::cout<<"number of queries before: " <<queries.size();
    
    // duplicate input until its large enough
    while (queries.size() < number_of_queries) {
        auto old_count = queries.size();
        queries.resize(2 * old_count);
        std::copy_n(queries.begin(), old_count, queries.begin() + old_count);
    }
    queries.resize(number_of_queries); // will reduce the amount of searches

    //time for building SA
    //
    auto t1 = high_resolution_clock::now();


    // Array that should hold the future suffix array
    std::vector<saidx_t> suffixarray;
    suffixarray.resize(reference.size()); // resizing the array, so it can hold the complete SA

    int *SA = (int *)malloc(reference.size() * sizeof(int));
    divsufsort(reinterpret_cast<sauchar_t const*>(reference.data()), SA, reference.size());
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "time for building the suffix arrray: "<< ms_double.count() << "ms\n"; 
    
    //!ImplementMe implement suffix array sort
    //Hint, if can use libdivsufsort (already integrated in this repo)
    //      https://github.com/y-256/libdivsufsort
    //      To make the `reference` compatible with libdivsufsort you can simply
    //      cast it by calling:
    //      `sauchar_t const* str = reinterpret_cast<sauchar_t const*>(reference.data());`
    
    //time for searching of query:
    auto t11 = high_resolution_clock::now();
    struct rusage r_usage;


    std::vector<char> T;
    for (int i=0; i<reference.size(); i++)
	    T.push_back(reference[i].to_char());
    
    int howoften=0;
    std::cout<<"number of queries: " <<queries.size();
    std::vector<int> occurences;
    std::vector<int> posi;
    for (auto& q : queries) {
	//if(howoften>=10){
	//	break;
	//}
   	int m = q.size();  // get length of pattern, needed for strncmp()
    	int n = reference.size();
	std::vector<char> q_char; //(q.begin(),q.end());
	for (int i=0; i<m; i++)
		q_char.push_back(q[i].to_char());

    // Do simple binary search for the pat in txt using the
    // built suffix array
    //
    // left search
    
	
	int LP;
	int RP;
	int l=0;
	int r=n-1;
	int M;
	if (q_char<=std::vector<char> (T.begin()+SA[0],T.begin()+SA[0]+m)){
		LP=0;
    	}	
	else if ( q_char>std::vector<char> (T.begin()+SA[n-1],T.begin()+SA[n-1]+m)){
		LP=n-1;
	}
    	else{	
		l=0;
		r=n-1;	
		while((r-l)>1){
			//std::cout<<"iteration:";
			M=std::ceil((l+r)/2.0);
			if (strcmp(std::string(begin(q_char),end(q_char)).c_str(),std::string(T.begin()+SA[M],T.begin()+SA[M]+m).c_str())<=0){
				       //	q_char<=std::vector<char> (T.begin()+SA[M],T.begin()+SA[M]+m)){
				r=M;
			}	
			else{
				l=M;
			}
		}
		LP=r;
		
		//find RP
		l=0;
		r=n-1;
		if ( q_char < std::vector<char>(T.begin()+SA[0],T.begin()+SA[0]+m))
			RP=0;
		else if(q_char >= std::vector<char>(T.begin()+SA[n-1],T.begin()+SA[n-1]+m))
			RP=n-1;	
		while((r-l)>1) {
			M=std::floor((l+r)/2.0);
			if ( std::vector<char>(T.begin()+SA[M], T.begin() + SA[M]+m) <=q_char){
				l=M;
			}
			else {
				r=M;
			}
		}	
		RP=l;
	}	

        if (LP<=RP){
		std::cout<<"Pattern found " << RP-LP+1 <<" times, first position: "<<SA[LP]<<std::endl;
			std::cout<<std::endl;
			occurences.push_back(RP-LP+1);
			for (int i=0; i<(RP-LP+1);i++)
				posi.push_back(SA[LP+i]);//can be simply adapted to print all positions

	}
	
	    //!TODO !ImplementMe apply binary search and find q  in reference using binary search on `suffixarray`
        // You can choose if you want to use binary search based on "naive approach", "mlr-trick", "lcp"
    
    howoften +=1;
    
    //std::cout<<"running " << howoften <<" times. \n";
    }
    auto t22 = high_resolution_clock::now();
    duration<double, std::milli> ms_double1 = t22 - t11;

    std::cout<< "time for searching of query: "<< ms_double1.count() << "ms\n";
    getrusage(RUSAGE_SELF,&r_usage);
    printf("Memory usage = %ld\n",r_usage.ru_maxrss);  
    //for (int i=0;i<occurences.size(); i++)
	  //std::cout<<occurences[i];
    //std::cout<<std::endl;

    std::ofstream output_file("./occurences.txt");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(occurences.begin(), occurences.end(), output_iterator);
    
    std::ofstream output_file2("./positions.txt");
    std::ostream_iterator<int> output_iterator2(output_file2, "\n");
    std::copy(posi.begin(), posi.end(), output_iterator2);


}
