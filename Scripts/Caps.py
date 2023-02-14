import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv('team_stats.csv')
df = df.sort_values(by=['Caps'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Caps'], 0.35, label='Caps')
ax.set_ylabel('Ghost caps')
ax.set_title('Ghost Caps by Team')
plt.savefig("TeamCaps.png")
plt.clf()

df = pd.read_csv('player_stats.csv')
df = df[(df['Caps'] > 0)]
df = df.sort_values(by=['Caps'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Caps'], 0.5, label='Caps')
ax.set_ylabel('Ghost caps')
ax.set_title('Ghost Caps by Player')
ax.set_yticks([0, 1, 2, 3, 4])
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("PlayerCaps.png")
plt.clf()
