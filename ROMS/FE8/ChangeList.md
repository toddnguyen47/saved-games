# Balanced Game 2.0

I'm not too fond of how the original Sacred Stones determined the maximum stats of its classes,
so I'll do my best to readjust them here. Note that this is my personal opinion.

# Change List

- Add "\_FE8EssentialFixes.txt" made by circles and edited by Snakey1

## Chapter Changes

- Chapter 5:
  - Can deploy 9 → 11 characters
  - Add 3 extra enemies (2 Fighters, 1 Soldier)
  - The Brigand will spawn on turn ~~6~~ → 7 and turn ~~8~~ → 9
    - Delay a turn so players can deal with the 3 extra enemies a bit easier. This way users can
      also have an additonal turn to save the northwest village.

## Characters

|          Lyn |   LV |   HP |  STR |  SKL |  SPD |  DEF |  RES |  LUK |
| ----------: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
|   Base Stats |    3 |    6 |    2 |   10 |   11 |    2 |    1 |    6 |
| Growth Rates |      |   70 |   40 |   60 |   60 |   20 |   30 |   55 |

- Similar base stats and same growth rates as Fire Emblem 7
- Can promote with Orion's Bolt

|       Kumoko |   LV |   HP |  STR |  SKL |  SPD |  DEF |  RES |  LUK |
| ----------: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
|   Base Stats |    2 |    0 |    0 |    0 |    0 |    0 |    1 |    3 |
| Growth Rates |      |   55 |   40 |   55 |   60 |   25 |   25 |   45 |

- A Mauthe Dogg just for fun. Has reduced Nino's (FE7) growth rates LOL
- Has innate +15 crit. Kumoko only
- Can promote with Orion's Bolt

|        Karla |   LV |   HP |  STR |  SKL |  SPD |  DEF |  RES |  LUK |
| ----------: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
|   Base Stats |    4 |    3 |    3 |    2 |    1 |    2 |    0 |    5 |
| Growth Rates |      |   85 |   55 |   40 |   45 |   30 |   15 |   35 |

- Balanced base stats of roughly the same STR, SKL, and SPD
- Similar growth rates to Raven from FE7. I want Karla to be a female Mercenary → Hero,
  and I imported some excellent Female Mercenary animation by Maiser6 and Serragirl, and
  Female Hero animation by Flasuban and Nuramon.

## Classes

- Sacaen Lord & Blade Lord
  - Added from Fire Emblem 7. I really like Lyn's animations.
  - Since Fire Emblem save game files can only load class up to `0x7F` (`0b1111111`, 7 bits), FE8
    already have 127 classes. Thus, two civilian classes (`0x71` and `0x72`) have to be replaced.
    If any civilians use the Sacaen Lord sprite, this is the reason.
  - Note that the Civilian base stats have NOT been changed. To compensate, Lyn have higher
    base stats than usual in her unique character base stats.
  - Lyn will join at the beginning of Chapter 3. She can be chosen as a unit starting from
    Chapter 4's preparation screen.
- Ephraim Great Lord
  - Max STR/MAG: 27 → 28
  - Max SKL: 26 → 28
  - Max SPD: 24 → 27
  - Can now use Swords
  - **EXPLANATION:** Ephraim has insane Growth rates, sporting 55/55/45 in STR/SKL/SPD, respectively.
    His class does NOT do his growth rates justice. On average (courtery of [serenesforest](https://serenesforest.net/the-sacred-stones/characters/average-stats/ephraim/) ), Ephraim will max out his STR at 20/16,
    his SKL at 20/11, and his SPD at 20/10. That's a little bit sad, in my opinion. Thus, I increased
    his max stats to better reflect his growth rates. His STR is increased by 1 so he should be
    maxing that out near 20/19 or 20/20, his SKL increased by 2 which he should max around 20/15,
    and his SPD is increased by 3 so he can max it around 20/15, as well. I feel like those levels
    should reflect where his stats should be maxed, instead of it nearing maxing out only at 20/10.
- Falcoknight
  - Initial SWD Level: E → D
  - Max SKL: 25 → 28
  - Max SPD: 28 → 30
  - **EXPLANATION:** Falcoknights are significantly weaker than Wyvern Knights. Buffing up their
    Max SKL and SPD to be more in line to Swordmaster's, and buff their STR to match Wyvern Knight's.
    In a way, Falcoknights should be similar to Swordmaster: they are fast, mobile units that do
    not hit hard but hit often. Hopefully with increased SKL and SPD caps, they reflect that play
    pattern more.
- General
  - Can no longer use swords.
  - Axe starting level: E → D
  - **EXPLANATION:** If they are tanky, have Great Shield (even though it does not activate often), and have
    excellent max stats, they should not control over the Weapon triangle as well, 5 movement speed
    be damned.
- Great Knight
  - Max SKL: (M) 24 → 25
  - **EXPLANATION:** Making sure the SUM of Max stats is the same as the (F) equivalent.
- Hero
  - Max STR: (M) 25 → 26, (F) 24 → 25
  - Max SPD: (F) 26 → 27
  - Max RES: (M) 22 → 23
  - **EXPLANATION:** Increasing Hero's MAX caps to match the Ranger's.
- Mage Knight
  - Max DEF: (M) 24 → 25
  - Max RES: (M) 25 → 26
  - Max SPD: (M) 25 → 26, (F) 25 → 26
  - **EXPLANATION:** Making sure the SUM of Max stats is the same as the (F) equivalent. Also tie
    the Sage class for SPD max as L'Arachel gets capped out too early on.
- Myrrh
  - When she joins in Ch 16, give her a Wretched Air.
  - Add Wretched Air animation.
  - **EXPLANATION:** Giving Myrhh a monster weapon so she can be of some use in your party.
- Paladin
  - Max STR: (M) 25 → 26, (F) 23 → 24
  - Max SKL: (M) 26 → 27, (F) 27 → 28
  - Max SPD: (M) 24 → 25, (F) 25 → 26
  - Able to use Axes and import axe animations.
  - **EXPLANATION:** Unpopular opinion, but I think the Paladin is outclassed by the Great Knight /
    General in this game. Perhaps it's because I play the game slowly that I think so... Anyhow, I made
    sure that the Paladin's Max SKL is at least equal to the General's Max SKL. Also, Paladins will
    be able to use Axes. This way, you can focus on the Paladin's strong point, which is their
    movement speed. You now have a solid option between (1) Paladin's Movement Speed, (2) Great
    Knight's overall utility, or (3) General's defensiveness.
- Ranger
  - Max STR: (F) 23 → 24
  - Max SKL: (F) 28 → 29
  - Gains ability to use Shamshir.
  - **EXPLANATION:** Equality! Female Rangers lost 2 points of max STR for NO reason, so I reallocated
    those 2 points here. As for Shamshir... that's just for fun. I wanted Eirika to have an option to
    promote into a Ranger, and
    she can use Shamshir so I thought, why not. In FE7 Rangers and Myrmidons both come from Sacae
    anyway (go Lyn!!!). Honestly Killing Edge is a better Shamshir anyway, and any sword classes
    can use Killing Edge so, this isn't game breaking or anything.
- Shaman & Druids
  - Imported Female Shaman & Druids standing map, moving map, and battle animations
  - On all maps, changed some Male classes to Female classes, including Shamans / Druids / Paladins, etc.
- Sniper
  - Gains +15% Crit skill.
  - **EXPLANATION:** Face it, Ranger beats Sniper in every single sense of the word. Giving the
    Sniper +15% Crit can hopefully give this class the extra oomph it needs to balance out the
    Ranger's superior max stats and ability to use swords.
- Swordmaster
  - Max STR: (F) 22 → 23
  - Max RES: (F) 25 → 24
  - **EXPLANATION**: Swordmasters don't need RES, whut. Moving one point of RES to STR for
    female Swordmasters (e.g. Marisa)
- Valkyrie
  - Max SPD: (M) 25 → 26, (F) 25 → 26
  - **EXPLANATION:** Tie the Sage class for SPD max as L'Arachel gets capped out too early on.
- Wight
  - Max STR: 24 → 28
  - Max SPD: 26 → 28
  - Max DEF: 22 → 23
  - Promotion Gains: HP: 4, STR: 2, SKL: 3, SPD: 2, DEF: 2, RES: 4
  - **EXPLANATION:** Another for fun stats, I wanted Ephraim of all things to be able to promote
    into a Wight. I made the Wight's Max stats similar to Ephraim's Great Lord adjusted max stats.
    This way, Great Lord has -1 max SPD but +1 Movement (7 MOV compared to Wight's 6). Of course,
    Wights also have the ability to wield Swords (including the Shamshir!). You can decide
    which class you want Ephraim to gear towards.
- Wyvern Lord
  - Max SKL: (M) 25 → 26, (F) 26 → 27
  - Max SPD: (M) 24 → 25, (F) 25 → 26
  - Max RES: (M) 23 → 24, (F) 24 → 25
  - **EXPLANATION:** I think Wyvern Lord is massively overshadowed by the Wyvern Knight class.
    Pierce is too good of a skill to pass up. Thus, I added some max stats to the Wyvern Lord class
    to make the choice slightly not as one-sided as before. Now, Wyvern Lords have a total of
    2 additional stats compared to the Wyvern Knight's total. With an extra 2 max stats and the
    ability to use swords, will that be enough to lift them up over Wyvern Knight? Only you can
    make that decision.

## Items

- Light spells cost reduced
  - **EXPLANATION:** In my opinion, I think Light spells are massively overshadowed by the Anima
    spells, and yet they are more expensive. I simply increased the usage per buy and reduced
    the cost per use a bit to even out the playing field a bit. I also increased their
    critical rate by 5 so they stand out from Anima a bit more.
  - Lightning:
    - Uses: 35 → 40
    - Price per use: 18 → 16 (Fire's is 14)
    - Critical: 5 → 10
  - Shine:
    - Uses: 30 → 35
    - Price per use: 30 → 24 (Thunder's is 20)
    - Critical: 8 → 13
  - Divine
    - Uses: 25 → 30
    - Price per use: 100 → 50 (Elfire's is 40... why?!?)
    - Critical: 10 → 15
- Add a ThunderStf (Thunder Staff) into the game
  - Unbreakable
  - Pow 2 / Hit 90 / Wt 4 / Crit 0 / Range 1-2
  - **EXPLANATION:** Add an unbreakable staff that does a bit of damage so you can train your
    clerics / priests a bit quicker. The ThunderStf will be available as an equipped staff on
    Moulder in Chapter 2 - The Protected.
  - ThunderStf will have [Black Lightning](https://drive.google.com/drive/u/1/folders/11k6XpgpapN4nmTAh6iwChYvD1_TXhzHt)'s animation.
  - Because of this, the Cleric and Priest animations had to be adjusted a little. In the following
    5 modes, the code `C06` had to be added to begin the opponent's turn, otherwise the game will
    freeze. `C06` usually precedes `C0D`. Interestingly enough, the Troubadour class already had
    code `C06` in the 5 modes mentioned below.
    - Mode 1: Melee Animation
    - Mode 3: Melee Critical Animation
    - Mode 5: Ranged Animation
    - Mode 6: Ranged Critical Animation
    - Mode 12: Attack Missed Animation
  - I also added Critical animations for Troubadours, Clerics, and Priests. I'm too lazy to add
    Staff critical animations for classes like Druids and Sages. Maybe in the future!

## Promotions

- Eirika is now a Mage! Her Lord class can use Anima and Dark. Her promoted class, Matriarch, can
  use Light and Staff. Essentially, her Matriarch class can use all 4 "magic" ranks!
  - Her max stats in Matriarch is the same as her previous Great Lord class.
  - Her seconadry promotion branch is a Mage Knight, if you want her to have more mobility
- Ephraim can now choose to promote to Wight in addition to her Great Lord class
  - Add Ephraim's palette (as much as I could) to Wight
  - **EXPLANATION:** Again, fun and giggles. Wight has +1 Max SPD and the ability to wield swords, but
    they have -1 MOV since they aren't mounted. Your choice!

# Event Pointers

- Ch. 16 event, giving both Sieglinde and Sigran:
  - `0x9F6A8C`, size 44 (`0x2C`)

# Old Palettes

- Gerik's old Hero Palette: `5553FF7FFF6B1F4B2E1DB62BB11E0C0A9877F36E4E5AD751B1406A28372EA514`
- Caellach's old Hero Palette: `5553FF7FFF6B1F4B2E1DF7317325EF189877F36E4E5AD161AB506438372EA514`
- Ross's old Hero Palette: `5553FF7FFF6B1F4B2E1DB55AEE494A3D9877F36E4E5A0D77C969E640372EA514`
- Garcia's old Hero Palette: `5553FF7FFF6B1F4B2E1DB55A0F4E6B419877F36E4E5AAD562659C64C372EA514`
- Karla's Swordmaster Palette: `5553FF7FFF4FFC2E9125B552CE354A21767F6F5ECA49DE7BD877125F0621A514`
- Eirika's old Lord Palette: `5553FF7FFF6B1F4B182A2E19B37F897A625DFF1B9E1A94011C0176086F0CA514`

# Credits

## Tools

- [FEBuilder](https://duckduckgo.com/?t=ffab&q=febuilder&ia=images)
- [FERecolor](https://forums.serenesforest.net/index.php?/topic/26748-fe-recolor/)
- [Usenti](http://www.coranac.com/projects/usenti/)

## Map Sprites

[Magi Sprite Link](https://drive.google.com/drive/u/1/folders/1bqjMQRUfITaB0rh2uG2JcxtSXYbltkxY)

- Saint(F) Moving and Standing by Melia
- Sage (F) Limstella Moving and standing by FE7if
- Shaman (F) by IS
- Druid (F) by IS

## Class Animations

- Female Mercenary: [\[T1\]\[swd\]\[Mercenary\](Tunic)\[F\]{Maiser6, Serragirl}](https://drive.google.com/drive/folders/1GB9IvafIpI4upH3iQohRS2HDFWzizxYu)
- Female Hero: [\[T2\]\[SWD\]\[Hero\](Armored +Pants)\[F\]{Nuramon}](https://drive.google.com/drive/folders/1w-SSEHt1a1t92TySyD-kck4zZuYNXbr3)
- Male Hero: [Nuramon Armored Pants](https://drive.google.com/drive/u/1/folders/1A_UsndWdmdrQWW4x35nGS1Nm42KjxMIa)
- Eirika Lord animation: [Limstella Alt by Zoisite and Greentea](https://drive.google.com/drive/u/1/folders/1W3AX6oce6GvYlVfYKkpMFzRAJ_o_jDPe)
- [Matriach by MrNight and DerTheVaporeon](https://drive.google.com/drive/u/1/folders/1cWUqc0niNVwIduMgblsngb_e6JHi5VtN)
- [Ephraim Sword Animation by eCut and Skitty](https://drive.google.com/drive/folders/1WiTQmM-DZRIMtesJTwazSgL4TU6WhqWJ)

## Spell Animations

- [Donbettyr Spell Animation](https://drive.google.com/drive/u/1/folders/1vbL1HNNbfBp4Y3U216Er6LpK-flUGUSm)
- [Super Thunderstorm by SHYUTERz](https://drive.google.com/drive/u/1/folders/1_O-fBWeHbj0mn9kBNU9wKx3YeU-qLGxU)
- Siegran animation: [\[Anima\](Super Thunderstorm){SHYUTERz}](https://drive.google.com/drive/u/1/folders/1_O-fBWeHbj0mn9kBNU9wKx3YeU-qLGxU)
- [Aqua by Alusq](https://drive.google.com/drive/u/1/folders/1h5s8EbtNtQs6ucJclT4SuvGTWc5mGazC)
  - Made a copy of Aqua to have melee animations
- [Ground Dasher by Bonzai & Blazer](https://drive.google.com/drive/folders/1lTCoXA9ETr0NjI3JCd_DFzjyZvqNBgKn)
  - Made a copy of Ground Dasher to have melee animations
- [Black Lightning (Melee and Ranged) by ThunderMage](https://drive.google.com/drive/u/1/folders/11k6XpgpapN4nmTAh6iwChYvD1_TXhzHt)
- [Sword Wave (sound edited) by lovemachine and Mikey Seregon](https://drive.google.com/drive/u/0/folders/11wkCucfl-zp-Dkdee7_EsQtnw8nci-5h)

# Weapon Icons

- [Ereshkiga Weapon Pack](https://drive.google.com/drive/u/1/folders/1mhRdpBcAgq8zPKar8zDr_MaVFsPOxSH5)
- [ThunderMage's icons](https://drive.google.com/drive/folders/1MkJ6z0jNftSSeufufBOIphG5GSNA4uLd)
- [Purple's Icons - Riptide icon](https://drive.google.com/drive/folders/17Il8haUQVcxWJThW8SkeTL2O1Riu-yl5)
- [Zane - icon_058](https://drive.google.com/drive/folders/1gm0BqJ_XqmQT02Np2dUmiChj2qG4VRUp)
