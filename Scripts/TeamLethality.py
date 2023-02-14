import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv('team_stats.csv')
df = df.sort_values(by=['Kills'], ascending=False)


fig, ax = plt.subplots()
ax.bar(df['Name'], df['Kills'], 0.25, label='kills')
ax.bar(df['Name'], df['Assists'], 0.35, label='assists')
ax.set_ylabel('Kills/assists')
ax.set_title('Kills and Assists by Team')
ax.legend()
plt.savefig("TeamLethality.png")
plt.clf()


fig, ax = plt.subplots()
ax.bar(df['Name'], df['Kills']/df['Maps'], 0.25, label='kills')
ax.bar(df['Name'], df['Assists']/df['Maps'], 0.35, label='assists')
ax.set_ylabel('Kills/assists per map')
ax.set_title('Average Kills and Assists per Map by Team')
ax.legend()
plt.savefig("TeamLethalityAvrg.png")
print("Done")