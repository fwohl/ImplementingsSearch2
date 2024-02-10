#include <sstream>
#include <fstream>

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

void findOccurences(std::vector<seqan3::dna5> const& txt, std::vector<seqan3::dna5> const& pat) {    	
	int M = pat.size();
	int N = txt.size();
	  	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) {
        	int j;
 
        /* For current index i, check for pattern match */
        	for (j = 0; j < M; j++)
            		if (txt[i + j].to_char() != pat[j].to_char() )
                	break;
 
        	if (j== M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
			    std::cout << "Pattern found at index " << i << std::endl;
    }
	
	
	//!TODO ImplementMe
}

int main(int argc, char const* const* argv) {
    seqan3::argument_parser parser{"naive_search", argc, argv, seqan3::update_notifications::off};

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
    std::vector<std::vector<seqan3::dna5>> reference;
    for (auto& record : reference_stream) {
        reference.push_back(record.sequence());
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
    

    auto t1 = high_resolution_clock::now();
    //! search for all occurences of queries inside of reference
    for (auto& r : reference) {
        for (auto& q : queries) {
            findOccurences(r, q);
        }
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double= t2-t1;
    std::cout<<"time for naive search: " <<ms_double.count()<<"ms\n";
    
    struct rusage r_usage;    
    getrusage(RUSAGE_SELF, &r_usage);
    std::ofstream outputfile;
    outputfile.open("memoryandruntime.txt");
    outputfile<<"memory: "<<r_usage.ru_maxrss<<"time: "<<ms_double.count()<<"ms\n";
    outputfile.close();


    return 0;
}
