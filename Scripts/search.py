import pandas as pd

df = pd.read_csv('player_stats.csv')
#df['avgKills'] = df['Kills']/df['Maps']
#df['avgAssists'] = df['Assists']/df['Maps']
#df['avgDeaths'] = df['Deaths']/df['Maps']
df['KDR'] = df['Kills']/df['Deaths']
df = df.sort_values(by=['KDR'], ascending=False)
print(df)

#df = pd.read_csv("wep_stats.csv")
#df['avrg'] = df['jitte']/df['Maps']
#df = df.sort_values(by=['avrg'], ascending=False)
#print(df)

df = pd.read_csv("team_stats.csv")
df['KDR'] = df['Kills']/df['Deaths']
df = df.sort_values(by=['KDR'], ascending=False)
#print(df)