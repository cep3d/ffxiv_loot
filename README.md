# ffxiv_loot
No special reason. Just because.

## Environment

- XCode 9.0
- macOS High Sierra 10.13.2

## Usage
```
$ ./loot-luck
ロットしてください。[(N)eed/(G)reed/(P)ass]N
Needしました。
Pass
[*]P1はアイテムにNeeedのダイスで94を出した。
   P2はアイテムにNeeedのダイスで42を出した。
   P3はアイテムにNeeedのダイスで93を出した。
   P4はアイテムにGreedのダイスで52を出した。
   P5はアイテムにNeeedのダイスで19を出した。
   P6はアイテムにGreedのダイスで10を出した。
   P7はアイテムにGreedのダイスで37を出した。
   P8はアイテムにGreedのダイスで50を出した。
P1はアイテムを手に入れた。
処理計測: 120 ms
```

## TODO
稀にランダム値が重複してしまう。

## 参考資料

### vectorコンテナにある構造体から最大値を取得する

https://stackoverflow.com/questions/16772477/how-to-get-min-or-max-element-in-a-vector-of-structures-in-c-based-on-some-fi


### コンソール文字の色変更

https://stackoverflow.com/questions/45526532/c-xcode-how-to-output-color


### 処理計測

http://en.cppreference.com/w/cpp/chrono
