import matplotlib.pyplot as plt
import pandas as pd

team = "WIN"
df = pd.read_csv('player_stats.csv')
df = df.loc[df['Team'] == team]

#df['avgKills'] = df['Deaths']/df['Maps']
#df = df.sort_values(by=['avgKills'], ascending=False)
#fig, ax = plt.subplots()
#ax.bar(df['Name'], df['Kills']/df['Maps'], 0.25, label='kills')
#ax.bar(df['Name'], df['Assists']/df['Maps'], 0.35, label='assists')
#ax.set_ylabel('Kills/assists per map')
#ax.set_title('Average Kills and Assists per Map by Team')
#ax.legend()
#plt.savefig("TeamDivs/" + team + "LethalityAvrg.png")
#print("Done")

df['avgDeath'] = df['Deaths']/df['Maps']
df = df.sort_values(by=['avgDeath'], ascending=False)
fig, ax = plt.subplots()
ax.bar(df['Name'], df['Kills']/df['Maps'], 0.5, label='Kills')
ax.bar(df['Name'], df['Deaths']/df['Maps'], 0.25, label='Deaths')
ax.set_ylabel('Average Kills/Deaths per map')
ax.set_title('Average Kills and Deaths per Map for ' + team)
ax.legend()
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("TeamDivs/" + team + "DeathsAvrg.png")
plt.clf()
print("Done " + team)

#print(df)