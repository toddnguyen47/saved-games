# Balanced Game 2.0

I'm not too fond of how the original Sacred Stones determined the maximum stats of its classes,
so I'll do my best to readjust them here. Note that this is my personal opinion.

# Change List

## Characters

|          Lyn |  LV |  HP | STR | SKL | SPD | DEF | RES | LUK |
| -----------: | --: | --: | --: | --: | --: | --: | --: | --: |
|   Base Stats |   3 |   6 |   2 |  10 |  11 |   2 |   1 |   6 |
| Growth Rates |     |  70 |  40 |  60 |  60 |  20 |  30 |  55 |

- Similar base stats and same growth rates as Fire Emblem 7

|        Karla |  LV |  HP | STR | SKL | SPD | DEF | RES | LUK |
| -----------: | --: | --: | --: | --: | --: | --: | --: | --: |
|   Base Stats |   4 |   3 |   3 |   2 |   1 |   2 |   0 |   5 |
| Growth Rates |     |  85 |  55 |  40 |  45 |  30 |  15 |  35 |

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
  - **EXPLANATION:** Ephraim has insane Growth rates, sporting 55/55/45 in STR/SKL/SPD, respectively.
    His class does NOT do his growth rates justice. On average (courtery of [serenesforest](https://serenesforest.net/the-sacred-stones/characters/average-stats/ephraim/) ), Ephraim will max out his STR at 20/16,
    his SKL at 20/11, and his SPD at 20/10. That's a little bit sad, in my opinion. Thus, I increased
    his max stats to better reflect his growth rates. His STR is increased by 1 so he should be
    maxing that out near 20/19 or 20/20, his SKL increased by 2 which he should max around 20/15,
    and his SPD is increased by 3 so he can max it around 20/15, as well. I feel like those levels
    should reflect where his stats should be maxed, instead of it nearing maxing out only at 20/10.
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
  - Max SPD: (F) 26 → 27
  - Max RES: (F) 24 → 23
  - **EXPLANATION:** Shifting around some max stats. Moved 1 stat from RES to SPD for
    female Heroes.
- Mage Knight
  - Max DEF: (M) 24 → 25
  - Max RES: (M) 25 → 26
  - **EXPLANATION:** Making sure the SUM of Max stats is the same as the (F) equivalent.
- Myrrh
  - When she joins in Ch 16, give her a Wretched Air.
  - Add Wretched Air animation.
  - **EXPLANATION:** Giving Myrhh a monster weapon so she can be of some use in your party.
- Paladin
  - Max SKL: (M) 26 → 27, (F) 27 → 28
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
- Great Knight
  - Max SKL: (M) 26 → 27
  - **EXPLANATION:** Making sure the SUM of Max stats is the same as the (F) equivalent.

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

## Spell Animations

- [Donbettyr Spell Animation](https://drive.google.com/drive/u/1/folders/1vbL1HNNbfBp4Y3U216Er6LpK-flUGUSm)
- Siegran animation: [\[Anima\](Super Thunderstorm){SHYUTERz}](https://drive.google.com/drive/u/1/folders/1_O-fBWeHbj0mn9kBNU9wKx3YeU-qLGxU)
- [Aqua by Alusq](https://drive.google.com/drive/u/1/folders/1h5s8EbtNtQs6ucJclT4SuvGTWc5mGazC)
