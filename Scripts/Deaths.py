import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv('team_stats.csv')
df['avgDeath'] = df['Deaths']/df['Maps']
df = df.sort_values(by=['avgDeath'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Kills']/df['Maps'], 0.5, label='Kills')
ax.bar(df['Name'], df['Deaths']/df['Maps'], 0.25, label='Deaths')
ax.set_ylabel('Average Kills/Deaths per map')
ax.set_title('Average Kills and Deaths per Map by Team')
ax.legend()
plt.savefig("TeamDeathsAvrg.png")
plt.clf()
print("Done")

df = pd.read_csv('player_stats.csv')
df['avgDeath'] = df['Deaths']/df['Maps']
df = df.sort_values(by=['avgDeath'], ascending=False)
df = df.iloc[1:10]
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Deaths']/df['Maps'], 0.5, label='Deaths')
ax.set_ylabel('Average deaths per map')
ax.set_title('Most Reckless')
ax.set_yticks(np.arange(9.5, 11.5, 0.1))
ax.set_ylim(9.5, 11.5)
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("PlayerTop10Deaths.png")
plt.clf()
print("Done")

df = pd.read_csv('player_stats.csv')
df['avgKills'] = df['Kills']/df['Maps']
df = df.sort_values(by=['avgKills'], ascending=False)
df = df.iloc[1:10]
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Kills']/df['Maps'], 0.5, label='Kills')
ax.set_ylabel('Average kills per map')
ax.set_title('Most Lethal')
ax.set_yticks(np.arange(11, 12.5, 0.1))
ax.set_ylim(11, 12.5)
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("PlayerTop10Kills.png")
plt.clf()
print("Done")

