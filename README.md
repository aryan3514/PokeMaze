# Pokemon Themed Maze Style Game



## Description
This game is based on the famous anime show "Pokemon". All the characters used are from the same. 

This game is made using SDL and its features, and it has been coded in C++ . (SDL, SDL IMAGE, SDL TTF, SDL MIXER)

All the rules of the game are given in the **Game Manual**!

But since, you're **here**, I can drop you a secret hint. **Team Rocket is not that lazy.**



## Requirements & Details 
- Microsoft Visual Studio 2019
- SDL, SDL2_image, SDL2_ttf, SDL2_mixer. (In case you don't have these installed, the method to install these is given in the installation process below.)
- Winsock.

This project was created on Microsoft Visual Studio 2019 (x86) (on Windows 10). 


## Installation

- In case you don't have Microsoft Visual Studio 2019 installed, you can install it from here : https://visualstudio.microsoft.com/downloads/.
- All the necessary SDL libraries are provided in these repository. (**NOTE : I do not own the rights of the SDL libraries.**)

### For the game :
1) First, create a **New Project** on Microsoft Visual Studio 2019.
2) Select **Empty Project** from the options provided (or search for Empty Project).

    ![g11](https://user-images.githubusercontent.com/78603679/124658774-cf207f80-dec1-11eb-8a77-a285a82570ef.png)

3) Once you create the project, Visual Studio will create a folder for that project in the location you selected. Go to that folder.

4) Inside the folder, you will see another folder with the same name as the project. Open it.

5) Download the code from this repository.

6) Paste the folders you downloaded into the folder you opened earlier. (folders : src, resources, sdl_all ) (The name of my project is PokemonGame)

    ![g2](https://user-images.githubusercontent.com/78603679/124659690-dbf1a300-dec2-11eb-8d38-7e37783ecfd8.png)
    
    
7) Now, open the project you created. Press **Shift + Alt + A** ! (This is to add the existing code into the project)

8) Once the browsing window pops up, go to the **src** folder you pasted, and select all the files. Click on **Add**.

     
9) Make sure the **Active Solution Platform** is set to **x86.** (Preferred)

   ![image](https://user-images.githubusercontent.com/78603679/124937413-0196bd80-e025-11eb-9576-c2ed9de8e606.png)

10) Go to the taskbar, and click on **Project->Properties**

11) Go to **Configuration Properties -> VC++ Directories**.

    ![image](https://user-images.githubusercontent.com/78603679/124661548-43105700-dec5-11eb-9372-9c009c41c1e5.png)


12) In the VC++ Directories tab, go to **Include Directories**. Click on **<Edit...>**.

    ![image](https://user-images.githubusercontent.com/78603679/124661709-7f43b780-dec5-11eb-8893-4f2570dc789e.png)


13) Click on the **New Line icon**, then click on the **Browse icon**.
    
    ![image](https://user-images.githubusercontent.com/78603679/124662648-bff00080-dec6-11eb-921d-521b1f4f47bd.png)


14) When the browsing window opens up, go to **sdl_all-> include**. Click on **Select Folder**. (sdl_all is where all the necessary SDL tools were pooled in)

    ![image](https://user-images.githubusercontent.com/78603679/124663020-2a08a580-dec7-11eb-9453-f3e0448f538c.png)

15) Go to **Library Directories** under the VC++ Directories tab, and follow the same procedure as done above till the browsing window opens.

16) Go to **sdl_all->lib->x86** (if you are using x86) and click on **Select Folder**.

    ![image](https://user-images.githubusercontent.com/78603679/124663522-d6e32280-dec7-11eb-942c-32a656aebfd9.png)

17) After completing the above steps, go to **Linker->Input** in the Project Properties tab.

    ![image](https://user-images.githubusercontent.com/78603679/124663695-0abe4800-dec8-11eb-8635-90f072f4617e.png)

18) Go to **Additional Dependencies-> <Edit...>**.

19) Paste the given contents in the space that appears. Click on **OK**. (the text given below is also given in sdl_all in copyme.txt)

``` 
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_ttf.lib
SDL2_mixer.lib
 ```

   ![image](https://user-images.githubusercontent.com/78603679/124664170-afd92080-dec8-11eb-832d-26f09e17ce30.png)
   
20) Click on **Apply**. Click on **OK**. 

21) Click on **Local Windows Debugger** to build the project. You will encounter an error. We built the program just to get access to the **Debug** folder of the project.

21) Now, open the project folder again. Go to the **Debug** folder.
    
    ![image](https://user-images.githubusercontent.com/78603679/124807090-099a2300-df7b-11eb-9bc3-e92c73bd8da8.png)
    
    
22) Copy all the files in **sdl_all->sdl dll files** folder, and paste them in that Debug folder.

(Note that if your project's name is "GameProject" then there will be two debug folders present :
     1) **GameProject->Debug**
     2) **GameProject->GameProject->Debug**
     You need to paste the files into the Debug folder in the first option.)

23) The installation is now complete!
    

### For Server Installation:

1) Follow Step 1-3 given above and create another project for the Server.

2)  Add the main.cpp file in the server to the project. (similar to step 8)

## Execution 

### Without Server Installation:
1) Click on **Local Windows Debugger** to build the game project.

    ![image](https://user-images.githubusercontent.com/78603679/124822170-30615500-df8d-11eb-8757-8621c7efcadd.png)

2) The game will start running.

### With Server Installation:
1) First, run the server file by clicking on **Local Windows Debugger** in the Server Project.

2) Now, run the **Local Windows Debugger** to build the game project (Ask all the players to run the game to connect).


## Resources 

1) https://lazyfoo.net/tutorials/SDL/

2) https://github.com/DarkMuffinJoe/Pacman

3) https://www.binarytides.com/winsock-socket-programming-tutorial/

4) https://github.com/SirFourier/Maze-generator-and-solver

5) https://stackoverflow.com/questions/60532245/implementing-a-recursive-backtracker-to-generate-a-maze

6) Google Images (for skins), and Youtube (for sound effects) 

**(I do not OWN THE RIGHTS of the skins and the sound effects used)**






