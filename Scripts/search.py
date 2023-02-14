import pandas as pd

#df = pd.read_csv('player_stats.csv')
#df['avgKills'] = df['Kills']/df['Maps']
#df['avgAssists'] = df['Assists']/df['Maps']
#df['avgDeaths'] = df['Deaths']/df['Maps']
#df['KDR'] = df['avgKills']/df['avgDeaths']
#df = df.sort_values(by=['Kills'], ascending=False)

df = pd.read_csv("wep_stats.csv")
df['avrg'] = df['jitte']/df['Maps']
df = df.sort_values(by=['avrg'], ascending=False)
print(df)