# FM Index with Pigeonhole Search

import time
import iv2py as iv
import os

def k_mismatch_search(index, query, k):
    """
    Perform k-mismatch search using FMIndex.
    """
    result_positions = set()

    # Iterate through all possible k-mismatch substrings
    for i in range(k + 1):
        mismatch_positions = index.search(query)
        mismatch_positions = [(pos, errors) for pos, errors in mismatch_positions if errors <= i]

        # Add the positions to the result set
        result_positions.update(mismatch_positions)

    return list(result_positions)

def hamming_distance(s1, s2):
    """
    Calculate the Hamming distance between two strings of equal length.
    """
    return sum(c1 != c2 for c1, c2 in zip(s1, s2))

def verify_search_results_all(reference, query, search_results, k):
    """
    Verify the accuracy of k-mismatch search results using Hamming distance for all sequences.
    """
    query_length = len(query)

    # Check if each position in the search results has Hamming distance within k of the query
    for result_position, errors in search_results:
        for i in range(len(reference)):
            substring = reference[i][result_position:result_position + query_length]

            if hamming_distance(query, substring) > k:
                print(f"Error: Position {result_position} does not have Hamming distance within {k} of the query for sequence {i}.")

# List the Human Genome files
genome_files = [
    'GCA_000001405.15_GRCh38_genomic.fna',
    'GCF_000001405.26_GRCh38_genomic.fna'
]

# Number of iterations
num_iterations = 100

# Dictionary to store total time per file and k value
total_time_per_file_k = {file: {k: 0 for k in range(3)} for file in genome_files}

# Load FM-index or create if it doesn't exist
fmindex_path = "genome.fmindex"
if os.path.exists(fmindex_path):
    index = iv.fmindex(path=fmindex_path)
else:
    reference_sequences = []
    for genome_file in genome_files:
        genome_file_path = '' + genome_file
        for record in iv.fasta.reader(file=genome_file_path):
            reference_sequences.append(iv.normalize(record.seq))

    index = iv.fmindex(reference=reference_sequences, samplingRate=16)
    index.save(fmindex_path)

# Perform k-mismatch search for k = 0, 1, 2
for k in range(3):
    for genome_file in genome_files:
        for _ in range(num_iterations):
            # Load Genome file
            genome_file_path = '' + genome_file
            for i, record in enumerate(iv.fasta.reader(file=genome_file_path)):
                # Consider the first 1,000 characters in the current sequence
                query_sequence = record.seq[:1000]

                # Measure the time for searching in the FMIndex with k-mismatch
                start_time = time.time()
                search_results = k_mismatch_search(index, query_sequence, k)
                end_time = time.time()

                # Accumulate the total time per file and k value
                total_time_per_file_k[genome_file][k] += end_time - start_time

                # Verify the search results using Hamming distance for all sequences
                verify_search_results_all(reference_sequences, query_sequence, search_results, k)

# Calculate the average time per file and k value
average_time_per_file_k = {file: {k: total_time / num_iterations for k, total_time in time_per_k.items()} for file, time_per_k in total_time_per_file_k.items()}

# Print the results
for file, time_per_k in average_time_per_file_k.items():
    for k, average_time in time_per_k.items():
        print(f"Average time for {num_iterations} iterations in {file} with k={k}: {average_time:.6f} seconds")
