# mcpi-block-shenanigans
 
A mod that improves the visuals of MCPI Reborn by modifying how blocks look, without adding any new blocks.

# Changes
## Lilypads
* If a flower-like block (saplings, sugarcane, flowers or grass) are placed above water, a lilypad appears below them.
* Placing these blocks on water is not implemented and you have to use the API to do so.

![Lilypads][lilypads]

## Flowering cacti
* Cacti has a 1/5 chance to be flowering.
* This makes a flower appear if the top block is air.

![Flowering cacti][cacti]

## Stars
* If you place a fire block with a nonzero id, it renders as a star.
* The star uses the redstone texture from `terrain.png`, overwrite it if you want the clean shape in the screenshot.
* The mod does not include the star generation code! Use [this](https://github.com/NikZapp/mcpi-stars-generator) python script to do so.

![Stars][stars]

## Sugarcane leaves
* The top of a sugarcane plant now has leaves. 
* This makes it look similar to bamboo.

![Sugarcane][sugarcane]

## Upcoming features
* Irregular wheat
* Stars not rendering in daylight
* Irregular farmland

[lilypads]: https://cdn.discordapp.com/attachments/1064039146248740915/1187329185102966834/2023-12-21_15.32.31.png?ex=65967d79&is=65840879&hm=02f0e3edab1233acdb3a255357814e9a5f2f30f79c9f814737c98ec02fecc65a&
[cacti]: https://cdn.discordapp.com/attachments/1064039146248740915/1187418705169227836/2023-12-21_21.29.54.png?ex=6596d0d8&is=65845bd8&hm=1a17e1d1f68fe430ceee1f6273324c7f542cefb715a85b1a408bfa8cd8987ccd&
[stars]: https://cdn.discordapp.com/attachments/602689326039433236/1188372778424999986/2023-12-21_22.23.39.png?ex=659a4965&is=6587d465&hm=78ba841adcaf32c4b4287430810939795626198d4700ba52b4abc331388985ac&
[sugarcane]: https://cdn.discordapp.com/attachments/1064039146248740915/1187410608077950976/2023-12-21_20.03.54.png?ex=6596c94d&is=6584544d&hm=ef02d48585b1710ad5e02bc8ea8dc4b6c8110a05bf564f891a81fb6a92ff784a&
