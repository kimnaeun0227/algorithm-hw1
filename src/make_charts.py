import csv
import matplotlib.pyplot as plt

INPUTS = ["Random", "Sorted", "Reverse", "Many Duplicates"]
ALGORITHMS = ["Selection", "Insertion", "Cocktail Shaker"]

data = {}

with open("results.csv", newline="") as f:
    reader = csv.DictReader(f)

    for row in reader:
        key = (row["Input"], row["Algorithm"])

        data[key] = {
            "time": float(row["AvgTime_ms"]),
            "comparisons": int(row["Comparisons"]),
            "moves": int(row["Moves"])
        }


def make_chart(metric, ylabel, title, filename):
    x = range(len(INPUTS))
    width = 0.25

    plt.figure(figsize=(10, 6))

    for index, algorithm in enumerate(ALGORITHMS):
        values = [
            data[(input_type, algorithm)][metric]
            for input_type in INPUTS
        ]

        positions = [
            position + (index - 1) * width
            for position in x
        ]

        plt.bar(
            positions,
            values,
            width=width,
            label=algorithm
        )

    plt.xticks(list(x), INPUTS)
    plt.xlabel("Input Type")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.grid(axis="y", alpha=0.3)
    plt.tight_layout()

    plt.savefig(filename, dpi=200)
    plt.close()


make_chart(
    "time",
    "Average Time (ms)",
    "Average Execution Time (N=4000)",
    "time_chart.png"
)

make_chart(
    "comparisons",
    "Number of Comparisons",
    "Comparisons by Input Type (N=4000)",
    "comparisons_chart.png"
)

make_chart(
    "moves",
    "Number of Moves",
    "Moves by Input Type (N=4000)",
    "moves_chart.png"
)

print("Charts created successfully.")
