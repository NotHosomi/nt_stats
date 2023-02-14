import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

weapon = "jitte"

df = pd.read_csv('wep_stats.csv')
df['avrg'] = df[weapon]/df['Maps']
df = df.sort_values(by=['avrg'], ascending=False)
df = df.iloc[0:10]
fig, ax = plt.subplots()
ax.bar(df['Name'], df['avrg'], 0.5, label='average per map')
ax.bar(df['Name'], df[weapon], 0.25, label='total')
ax.set_ylabel(weapon + ' kills')
ax.set_title('Top 10 '+weapon+' users')
ax.legend()
plt.setp(ax.get_xticklabels(), rotation=45, ha='right')
plt.tight_layout()
plt.savefig("WeaponTop10-"+weapon+".png")
plt.clf()
print("Done")