import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

def visualize_results(csv_file, input_size, title, filename):
    # Load the CSV file
    df = pd.read_csv(os.path.join("results", csv_file))
    df = df[df['input_size'] <= input_size]
    # Extract unique algorithms
    algorithms = df['algorithm'].unique()
    colors = ["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd", "#8c564b"]  # Contrasting colors
    
    # Plot each algorithm's performance
    plt.figure(figsize=(10, 6))
    for i, algo in enumerate(algorithms):
        subset = df[df['algorithm'] == algo]
        plt.plot(subset['input_size'], subset['execution_time'], linestyle='-', color=colors[i % len(colors)], label=algo)
    
    plt.xlabel("Input Size (N)")
    plt.ylabel("Execution Time (ms)")
    plt.title(title)
    plt.legend()
    plt.grid()
    plt.savefig(os.path.join("plots", filename), dpi=1200, bbox_inches='tight')


def visualize_results_smooth(csv_file, input_size,  title, filename, show_ticks = False):
    
    # Load the CSV file
    df = pd.read_csv(os.path.join("results", csv_file))
    df = df[df['input_size'] <= input_size]
    
    # Extract unique algorithms
    algorithms = df['algorithm'].unique()
    
    # Plot each algorithm's performance
    plt.figure(figsize=(12, 6))
    
    for algo in algorithms:
        subset = df[df['algorithm'] == algo]
        x = subset['input_size']
        y = subset['execution_time']
        
        # Smooth the curve using a rolling mean
        smoothed_y = np.convolve(y, np.ones(10)/10, mode='valid')
        smoothed_x = x[:len(smoothed_y)]  # Adjust x to match y length
        
        plt.plot(smoothed_x, smoothed_y, marker='', linestyle='-', label=algo)
    
    plt.xlabel("Input Size (N)")
    plt.ylabel("Execution Time (ms)")
    plt.title(title)
    
    plt.legend()
    plt.grid()

    if show_ticks:
        tick_density = input_size
        # Dynamically set x-axis ticks for better visibility of the meeting point
        num_ticks = min(tick_density, len(df['input_size'].unique()))  # Ensure we don’t exceed unique input sizes
        tick_positions = np.linspace(df['input_size'].min(), df['input_size'].max(), num=num_ticks, dtype=int)
        plt.xticks(tick_positions, rotation=45)  # Rotate for better readability
    
    plt.savefig(os.path.join("plots", filename), dpi=1200, bbox_inches='tight')

visualize_results(
    csv_file = "insertion_vs_quick_small.csv", 
    input_size = 256, 
    title = "Insertion Sort Vs Quick Sort", 
    filename = "insertion_vs_quicksort.png"
)

visualize_results_smooth(
    csv_file = "insertion_vs_quick_small.csv", 
    input_size = 35, 
    title = "Insertion Sort Vs Quick Sort Cutoff Value", 
    filename = "insertion_vs_quicksort_cutoff.png", 
    show_ticks = True
)

visualize_results(
    csv_file = "insertion_quick_random_small.csv", 
    input_size = 256, 
    title = "Insertion Sort Vs Quick Sort (Random Pivot)", 
    filename = "insertion_vs_quicksort_random_pivot.png"
)

visualize_results_smooth(
    csv_file = "insertion_quick_random_small.csv", 
    input_size = 70, 
    title = "Insertion Sort Vs Quick Sort (Random Pivot) Cutoff Value", 
    filename = "insertion_vs_quicksort_random_pivot_cutoff.png", 
    show_ticks = True
)

visualize_results(
    csv_file = "insertion_quick_3median_small.csv", 
    input_size = 256, 
    title = "Insertion Sort Vs Quick Sort (3 Median Pivot)", 
    filename = "insertion_vs_quicksort_3median_pivot.png"
)

visualize_results_smooth(
    csv_file = "insertion_quick_3median_small.csv", 
    input_size = 60, 
    title = "Insertion Sort Vs Quick Sort (3 Median Pivot) Cutoff Value", 
    filename = "insertion_vs_quicksort_3median_pivot_cutoff.png", 
    show_ticks = True
)

visualize_results(
    csv_file = "quicksort_comparison_small.csv", 
    input_size = 256, 
    title = "Quick Sort Comparison", 
    filename = "quick_sort_comparison.png"
)

visualize_results_smooth(
    csv_file = "quicksort_comparison_small.csv", 
    input_size = 256, 
    title = "Quick Sort Comparison (Smooth Curve)", 
    filename = "quick_sort_comparison_smooth.png", 
    show_ticks = False
)

visualize_results(
    csv_file = "hybrid_quicksort_comparison_small.csv", 
    input_size = 256, 
    title = "Quick Sort (Hybrid) Comparison", 
    filename = "quick_sort_hybrid_comparison.png"
)

visualize_results_smooth(
    csv_file = "quick_sort_nh_vs_h_small.csv", 
    input_size = 256, 
    title = "Quick Sort Pure Vs Hybrid (Smooth Curve)", 
    filename = "quick_sort_nh_vs_h_smooth.png", 
    show_ticks = False
)

visualize_results(
    csv_file = "radixsort_comparison_small.csv", 
    input_size = 256, 
    title = "Radix Sort Comparison for Best Base", 
    filename = "radix_sort_comparison.png"
)

def visualize_single_radix(csv_file, input_size, title, filename):
    # Load the CSV file
    df = pd.read_csv(os.path.join("results", csv_file))
    df = df[df['input_size'] <= input_size]
    # Extract unique algorithms
    algorithms = df['algorithm'].unique()
    colors = ["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd", "#8c564b"]  # Contrasting colors
    
    # Plot each algorithm's performance
    plt.figure(figsize=(10, 6))
    for i, algo in enumerate(algorithms):
        subset = df[df['algorithm'] == algo]
        plt.plot(subset['input_size'], subset['execution_time'], linestyle='-', color=colors[i % len(colors)], label=algo)
    
    plt.xlabel("Base")
    plt.ylabel("Execution Time (ms)")
    plt.title(title)
    plt.xscale("log", base = 2)
    plt.legend()
    plt.grid()
    plt.savefig(os.path.join("plots", filename), dpi=1200, bbox_inches='tight')

visualize_single_radix(
    csv_file = "radixsort_singledata_small.csv", 
    input_size = 16384, 
    title = "Radix Sort Comparison for Best Base with Size 256", 
    filename = "radix_sort_comparison_single.png"
)

def plot_sorting_performance(csv_file):
    # Load the CSV file
    df = pd.read_csv(os.path.join("results", csv_file))

    # Extract unique algorithms
    algorithms = df['algorithm'].unique()

    # Create figure
    plt.figure(figsize=(10, 6))

    # Define colors for better distinction
    colors = {
        "quick_sort_pure": "blue",
        "insertion_sort": "orange",
        "radix_sort_base_256": "red"
    }

    # Plot each algorithm
    for algo in algorithms:
        subset = df[df['algorithm'] == algo]
        plt.plot(subset['input_size'], subset['execution_time'], marker='o', linestyle='-', label=algo, color=colors.get(algo, "black"))

    # Set labels and scales
    plt.xlabel("Input Size (N)")
    plt.ylabel("Execution Time (ms)")
    plt.xscale("log", base=2)  # Log scale for input size
    # plt.yscale("log", base=2)  # Log scale for execution time

    # Set Y-axis limits to improve readability
    plt.ylim(0.0001, 10)  # Adjust based on dataset

    plt.title("Insertion Sort VS Best Quick Sort VS Radix Sort with Base 256 (Large Input)")

    # Add legend and grid
    plt.legend()
    plt.grid()

    plt.savefig(os.path.join("plots", "all_sort_comparison_large"), dpi=1200, bbox_inches='tight')

plot_sorting_performance("quicksort_insertion_radixsort_comparison_large.csv")
