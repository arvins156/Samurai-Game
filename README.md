<img src="https://github.com/user-attachments/assets/e6ea854b-2188-42e7-a533-b889343e7800" alt="drawing" width="300"/>

## Description

Samurai Game is a PvP multiplayer, sword-fighting action game. It is set in third-person, and the objective is to battle against another player in a fighting arena using katanas, combos, and abilities. The game can have multiple characters to play as, each with their own class and statistics. There may also be multiple stages, including static and moving stages, allowing players to use their creativity and create interesting fighting dynamics. Unreal Engine 5 is used as the game engine for its high-quality graphics, as well as programming in a user-friendly visual language alongside development in C++. On the technical side, the game can use peer-to-peer networking and Steam’s Online Subsystem API to enable multiplayer connectivity. The game is estimated to take around 1-2 years of development.

## Use

To clone this repository:

* In a command line window with [Git](https://git-scm.com/) or
* On Windows, use [Git Bash](https://git-scm.com/download/win) to execute the commands below
```sh
# Navigate into your desired repository
$ cd (name of the directory of your choice)

# Clone this repository
$ git clone https://github.com/arvins156/Samurai-Game.git
```

* Alternatively, you may use [GitHub Desktop](https://desktop.github.com/download/) for a more visual workflow

### Launching the editor

You will need to build from source using Unreal Engine 5.5. 


* In the folder you created, run the [SamuraiGame.uproject](https://github.com/arvins156/Samurai-Game/blob/main/SamuraiGame.uproject) file
* This will build the project and fulfil the dependencies
* If for any reason the project fails to build, remove the Binaries, Intermediate and Saved folders generated and attempt to build again. As an extension, you should not commit these folders to the GitHub repository as they are local files 
* Once the project is successfully built, Unreal Engine will open and you will be able to make changes in the editor
* For programming, it is recommended to use [JetBrains Rider IDE](https://www.jetbrains.com/rider/) for its integration with C++ Unreal Engine development
