#!/bin/python3

import sys

def largest_product_in_grid(grid):

    maxprod = 0

    for i in range(0, 20):
        for j in range(3, 23):
            prod_row = grid[i][j] * grid[i][j+1] * grid[i][j+2] * grid[i][j+3]
            prod_col = grid[i][j] * grid[i+1][j] * grid[i+2][j] * grid[i+3][j]
            prod_dil = grid[i][j] * grid[i+1][j-1] * grid[i+2][j-2] * grid[i+3][j-3]
            prod_dir = grid[i][j] * grid[i+1][j+1] * grid[i+2][j+2] * grid[i+3][j+3]

            maxprod = max([maxprod, prod_row, prod_col, prod_dil, prod_dir])
    
    return maxprod

grid = []
for grid_i in range(20):
    grid_t = [0,0,0]
    grid_t += [int(grid_temp) for grid_temp in input().strip().split(' ')]
    grid_t += [0,0,0]
    grid.append(grid_t)

grid.append([0]*26)
grid.append([0]*26)
grid.append([0]*26)

res = largest_product_in_grid(grid)
print(res)

