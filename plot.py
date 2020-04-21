#!/usr/bin/env python3

from matplotlib import pyplot as plt
import argparse
import csv
import numpy as np

def main(args):
    alpha = 0.40 if args.average else 1

    with open('out.csv', newline='') as csvfile:
        reader = csv.reader(csvfile)
        data = []
        for row in reader:
            data.append([])
            next_row = row
            title = row[0]
            data[-1] = [int(x) for x in row[1:-1]]
            plt.plot(data[-1], label=f'{title}', alpha=alpha)

        if args.average:
            avg = np.array(data)
            plt.plot(list(np.average(avg, axis=0)), label="average")

        plt.legend(bbox_to_anchor=(1, 1), loc='upper right', ncol=1)
        plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--average", help="plot the average", action='store_true')
    args = parser.parse_args()
    main(args)
