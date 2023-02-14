import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv('map_stats.csv')
df = df.sort_values(by=['Plays'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Plays'], 0.5, label='Plays')
ax.set_ylabel('Number of plays')
ax.set_title('Maps Played')
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("MapPlays.png")
plt.clf()
print("Done")

df["avrgCaps"] = df['Caps']/df['Plays']
df = df.sort_values(by=['avrgCaps'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['avrgCaps'], 0.5, label='avrgCaps')
ax.set_ylabel('Average number of caps')
ax.set_title('Ghost Caps per Play by Map')
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("MapCaps.png")
plt.clf()
print("Done")

df["avrgKills"] = df['Kills']/df['Plays']
df = df.sort_values(by=['avrgKills'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['avrgKills'], 0.5, label='avrgKills')
ax.set_ylabel('Average number of kills')
ax.set_title('Kills per Play by Map')
ax.set_ylim(70, 100.1)
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("MapKills.png")
plt.clf()
print("Done")