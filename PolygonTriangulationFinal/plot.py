import matplotlib.pyplot as plt

# Read vertices from file
with open('output.txt') as f:
    content = f.readlines()

# Process vertices for each test case
vertices_list = []
i = 0
num_skipped = 0

while i < len(content) and len(vertices_list) < 40:
    n = int(content[i].strip())
    vertices = []
    for j in range(n):
        x, y = map(int, content[i+j+1].strip().split())
        vertices.append((x, y))
    vertices_list.append(vertices)
    i += 5*(n + 1)
    


# Plot vertices and lines for each test case
fig = plt.figure(figsize=(600, 600))
fig.set_figheight(50)
 

fig.set_figwidth(50)
fig.suptitle("Showing a Subsample of Testcases")


for i, vertices in enumerate(vertices_list):
    ax = plt.subplot(5, 8, i+1)
    ax.scatter(*zip(*vertices))
    ax.plot(*zip(*(vertices + [vertices[0]])), color='r')
    ax.set_title(f'Test case {i+1}')
plt.savefig("fig_sub.jpg")
plt.show()
