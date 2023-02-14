import pandas as pd

df = pd.read_csv('player_stats.csv')
df['avgAssists'] = df['Assists']/df['Maps']
#df['avgKills'] = df['Kills']/df['Maps']
#df['avgDeaths'] = df['Deaths']/df['Maps']
#df['KDR'] = df['avgKills']/df['avgDeaths']
df = df.sort_values(by=['avgAssists'], ascending=False)
print(df)