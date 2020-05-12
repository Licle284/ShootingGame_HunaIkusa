# ShootingGame_HunaIkusa

シューティングゲーム「船戦」


・砲台を積んだ船を操作し、多種の弾道を使い分け、先に敵の船を倒すシューティングゲーム。

・数値計算を使用して波の動き表現し、波に合わせて船が変化する。チャージと弾種切り替えによって、10パターン以上の弾を放つ。　

使用言語：　　C++

開発環境：　　Windows8.1　VisualStudio2017

ライブラリ：　DXライブラリ

------
ゲーム中の操作方法

バトル中の操作方法 :
プレイヤーは青い船を操縦します。
1. 方向キーの「左」と「右」で船を動かすことができます。船は海面から離れることはありません。また画面の端へも行くことができません。

2. 方向キーの「上」と「下」で砲台の角度を調整します。

3. 「スペースキー」で弾を発射します。敵にあたるとダメージを与えることができ、相手の弾に当たるとダメージを受けます。

4. 発射する弾は、「放物線弾」、「直線弾」、「海面弾」、「正弦波弾」の4種類です。「W」を押すことで弾を切り替えることができます。

5. 「スペースキー」を長押し、放した時にチャージ弾が放てます。チャージ中は左上のゲージが溜まります。ゲージの溜まり具合によりチャージ弾の軌道や個数が変化します。

6. 敵の船にぶつかると、プレイヤーの船は大ダメージを受けてしまいます。

7. 難易度は4段階で、一度クリアしてタイトルに戻るごとに難易度が更新されます。



使用音素材 : 
魔王魂　https://maoudamashii.jokersounds.com/






参考サイト：
--------------
ポンクソフト   https://ponk.jp/  2020/2/16
Copyright c 2002 naga3

Permission is hereby granted, free of charge, to any person obtaining a copy 

of this software and associated documentation files (the "Software"), to 

deal in the Software without restriction, including without limitation the 

rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 

sell copies of the Software, and to permit persons to whom the Software is 

furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 

all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 

FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 

IN THE SOFTWARE.
*/


力学アルゴリズムによる波のシミュレーション（線上の波）- VCSSL
https://www.vcssl.org/ja-jp/code/archive/0001/1100-string-wave/  2020/2/19





