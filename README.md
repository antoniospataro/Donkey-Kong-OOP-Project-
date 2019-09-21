Donkey Kong (OOP Project with Allegro) 

[![Watch the video](https://i.imgur.com/ST0QkxC.png)](https://www.youtube.com/watch?v=RMV6-3SdDWg&t=11s)


Tested on Linux (Ubuntu 19.10) / macOS (majove)

# Dep

* Make
* Java 8+
* Gradle

```
make dep-install
```

# Run

Game
```
make run
```

|key|Action|
|---|------|
|Space | Jump |
|Arrow Up | Climb Stair |
|Arrow Left | Walk Left |
|Arrow Right | Walk Right |
|Esc | Exit |
|Enter | Enter |
|s | Change Stage/Map |
|m | Mute sound |


Editor
```
make run-editor
```

|key|Action|
|---|------|
|1 | Floor |
|2 | Stair |
|3 | Barrel |
|r | Reset |
|s | Save on DKEditor/core/assets/BonusLevel.map|

Copy the saved map file BonusLevel.map to Maps/Map[N].map 

```
cp DKEditor/core/assets/BonusLevel.map Maps/Map1.map
```

Format

```
make format
```


# Ref 

* https://liballeg.org/a5docs/trunk/

* https://libgdx.badlogicgames.com/download.html