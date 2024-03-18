import matplotlib.pyplot as plt

# Read data from file 1
with open("dp_time.txt", "r") as f:
    data1 = list(map(int, f.readlines()[:570]))

# Calculate average of each 30 numbers from file 1

n1 = len(data1)
step = 30
avg1 = [sum(data1[i:i+step])/step for i in range(0, n1, step)]

# Read data from file 2
with open("brute_force_time.txt", "r") as f:
    data2 = list(map(int, f.readlines()[:570]))

# Calculate average of each 30 numbers from file 2

n2 = len(data2)
avg2 = [sum(data2[i:i+step])/step for i in range(0, n2, step)]

# Plot the averages from both files
fig, ax = plt.subplots()
ax.plot(range(3, len(avg1)+3), avg1, 'b.-', label='DP')
ax.plot(range(3, len(avg2)+3), avg2, 'r.-', label='Brute Force')
ax.set_xlabel('Number of Vertices')
ax.set_ylabel('Time Taken (in ms)')
ax.set_title('Average Time Taken')

ax.legend()
fig.set_size_inches(10, 8)

plt.savefig('dp_vs_brute.jpg')
plt.show()
