#!/usr/bin/env python3
import os
import argparse
import matplotlib.pyplot as plt


FONT_SIZE = 14

def parse_trajectory(path):
    """
    
    """

    data = {"t": [], "x": [], "y": [], "yaw": []}
    with open(path, 'r') as f:
        keys = f.readline().rstrip().split(' ')  # get keys from first line, remove '/n'
        for line in f.readlines():
            line = line[0:-1].split(' ')
            for i in range(len(keys)):
                data[keys[i]].append(float(line[i]))

    return data

def save_plot(path):
    """Saves graph to the output pkg"""

    folder_path = path
    name = "graph"

    print("folder_path: ", folder_path)
    print("name: ", name)

    pwd = os.getcwd()
    os.chdir(os.path.expanduser('~'))
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
        
    os.chdir(folder_path)
    plt.savefig('{}.png'.format(name))
    os.chdir(pwd)

def plot_data(data):
    """

    """

    # Initialise the subplot function using number of rows and columns
    figure, axis = plt.subplots(2, 2)
      
    # For X(t) function
    axis[0, 0].plot(data['t'], data['x'])
    axis[0, 0].set_title("x(t)")

    # For Y(t)
    axis[0, 1].plot(data['t'], data['y'])
    axis[0, 1].set_title("y(t)")
      
    # For YAW(t)
    axis[1, 0].plot(data['t'], data['yaw'])
    axis[1, 0].set_title("yaw(t)")
      
    # For Y(X)
    axis[1, 1].plot(data['x'], data['y'])
    axis[1, 1].set_title("y(x)")
      

    # Combine all the operations and display
    # plt.show()


def main():
    """ """

    plt.rcParams['font.size'] = FONT_SIZE

    parser = argparse.ArgumentParser()
    parser.add_argument('-input', action='store', dest='input',
                        required=True, help='absolute path to the data')
    
    parser.add_argument('-output', action='store', dest='output', 
                        required=False, default="", 
                        help="absolute path to the output folder to store images")

    args = parser.parse_args()

    print("input_path: ",args.input)

    data = parse_trajectory(args.input)

    plot_data(data)

    if(args.output):
        save_plot(args.output)

    plt.show()

if __name__ == "__main__":
    main()
