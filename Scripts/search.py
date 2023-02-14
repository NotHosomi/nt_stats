import pandas as pd

df = pd.read_csv('player_stats.csv')
df['avgKills'] = df['Kills']/df['Maps']
df['avgAssists'] = df['Assists']/df['Maps']
df['avgDeaths'] = df['Deaths']/df['Maps']
df['KDR'] = df['avgKills']/df['avgDeaths']
df = df.sort_values(by=['avgDeaths'], ascending=False)
print(df)