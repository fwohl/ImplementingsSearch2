#include <divsufsort.h>
#include <sstream>
typedef int32_t saint_t;
typedef int32_t saidx_t;
typedef uint8_t sauchar_t;



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

    //!TODO !ImplementMe implement suffix array sort
    //Hint, if can use libdivsufsort (already integrated in this repo)
    //      https://github.com/y-256/libdivsufsort
    //      To make the `reference` compatible with libdivsufsort you can simply
    //      cast it by calling:
    //      `sauchar_t const* str = reinterpret_cast<sauchar_t const*>(reference.data());`
    sauchar_t const* str = reinterpret_cast<sauchar_t const*>(reference.data());

    divsufsort(str, suffixarray.data(), static_cast<saidx_t>(suffixarray.size()));

    std::cout << suffixarray.at(10) <<std::endl;

    for (auto& q : queries) {
        //!TODO !ImplementMe apply binary search and find q  in reference using binary search on `suffixarray`
        // You can choose if you want to use binary search based on "naive approach", "mlr-trick", "lcp"

        

        int n = suffixarray.size();
        int m = q.size();

        int Lp, Rp;

            // Compare q with the suffix starting from suffixarray[0]
        if (std::lexicographical_compare(q.begin(), q.end(), reference.begin() + suffixarray[0], reference.end())) {
            Lp = 0;
        } else if (std::lexicographical_compare(reference.begin() + suffixarray[n - 1], reference.end(), q.begin(), q.end())) {
            Lp = n;
        } else {
            int L = 0, R = n - 1;

            while (R - L > 1) {
                int M = std::ceil((L + R) / 2.0);
                if (std::lexicographical_compare(q.begin(), q.end(),
                                                reference.begin() + suffixarray[M], reference.begin() + suffixarray[M] + m)) {
                    R = M;
                } else {
                    L = M;
                }
            }
            Lp = R;

            L = 0;
            R = n - 1;

            while (R - L > 1) {
                int M = std::ceil((L + R) / 2.0);
                if (std::lexicographical_compare(reference.begin() + suffixarray[M], reference.begin() + suffixarray[M] + m,
                                                q.begin(), q.end())) {
                    L = M;
                } else {
                    R = M;
                }
            }
            Rp = R;
        }

        std::pair found_suffix = std::make_pair(Lp, Rp);
        std::cout << "pattern: " << " found at starting between " << Rp << " and "<< Lp <<std::endl;
	for (auto x: std::vector<seqan3::dna5> (reference.begin()+suffixarray[Lp-1],reference.begin()+suffixarray[Lp-1]+m))
		std::cout<<x.to_char();
		std::cout<<std::endl;
	for (auto qu : q)
		std::cout<<qu.to_char();
		std::cout<<std::endl;



    }

    return 0;
}


