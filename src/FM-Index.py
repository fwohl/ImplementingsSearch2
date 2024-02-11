# FM Index Search

# Initialize
# Ensure to run these commands in your environment:
# pip install iv2py
# pip install biopython

# Edit the file paths for the reference and Illumina files for your local configuration

# Construct the structure

import iv2py as iv
import os
import time

# Load or create FM index
fmindex_path = "file.fmindex"
if os.path.exists(fmindex_path):
    # Load FM index from disk
    index = iv.fmindex(path=fmindex_path)
else:
    # Load FASTA file - normalize sequences (e.g., make everything uppercase, check for invalid characters)
    reference_path = '/content/drive/MyDrive/data/hg38_partial.fasta'
    reference = [iv.normalize(rec.seq) for rec in iv.fasta.reader(reference_path)]

    # Build FM index
    index = iv.fmindex(reference=reference, samplingRate=16)
    index.save(fmindex_path)

# Check if the file imports ok
fasta_file_path = '/hg38_partial.fasta'
for record in iv.fasta.reader(file=fasta_file_path):
    print("ID:", record.id)
    print("First 10 letters of Sequence:", record.seq[:10])
    print("\n")

# Define Illumina files
illumina_files = [
    'illumina_reads_100.fasta',
    'illumina_reads_40.fasta',
    'illumina_reads_60.fasta',
    'illumina_reads_80.fasta'
]

# Number of iterations
num_iterations = 100

# Function to calculate and print results
def calculate_and_print_results(illumina_file, chunk_size):
    total_time = 0
    illumina_file_path = '/' + illumina_file
    for _ in range(num_iterations):
        for record in iv.fasta.reader(file=illumina_file_path):
            # Consider the specified number of characters in the current sequence
            reference_text_chunk = record.seq[:chunk_size]

            # Measure the time for searching in the FMIndex
            start_time = time.time()
            res = index.search(reference_text_chunk)
            end_time = time.time()

            # Accumulate the total time
            total_time += end_time - start_time

    # Calculate the average time
    average_time = total_time / num_iterations
    print(f"Average time for {num_iterations} iterations in {illumina_file} ({chunk_size} characters): {average_time:.6f} seconds")

# Iterate over different chunk sizes
chunk_sizes = [1000, 10000, 100000, 1000000]
for chunk_size in chunk_sizes:
    for illumina_file in illumina_files:
        calculate_and_print_results(illumina_file, chunk_size)
