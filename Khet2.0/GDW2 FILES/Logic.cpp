//// This file is Pseudo coded only because we're missing like half the things we need for this.
//
//// Game state will be an Int between 0 and 3? <-- however many states we need
//// 0 = main menu
//// 1 = in-game (Shows the board)
//// 2	= instruction menu?
//// 3 = options (If we allow for customizable options such as player colours etc. can just be empty or in-progress)
//
//// -1 = quitting (Literally anything out of range of the while loops)
//
//// int gamestate;
//
//While(programIsRunning)
//{
//	gamestate = 0; // defaults if you somehow force yourself out of a while?
//
//
//	// MENU GAMESTATE
//	while (gamestate == 0)
//	{
//		displayMainMenu();
//		(get user input)
//
//		if(input == quit)
//		{
//			gamestate = -1;
//			programIsRunning = false;
//		}
//
//		if(input == play)
//		{
//			
//			loadgame(getBoardConfig(ie: classic));  // Basically all of main goes here lol?
//			displayBoard();
//			gamestate = 1;
//
//		}
//
//		if (input == howToPlay)
//		{
//
//			loadInstructions();
//			gamestate = 2;
//
//		}
//
//		if (input == options)
//		{
//
//			loadOptions();
//			gamestate = 3;
//
//		}
//
//
//	}
//	//MENU GAME STATE CLOSED
//
//
//	//IN GAME
//
//	// int turn = 1;
//	while (gamestate == 1)
//	{
//		(await user input);
//
//		if (turn == 1)
//		{
//			//playermove needs move validation, the program should wait for a valid move to be choosen before updating the board.
//			playerMove(1);	//Player move should take in the turn integer, if piece.player == turn then valid piece to move.
//		}
//		else
//			playerMove(2);
//
//		updateBoard();
//		
//		firelaser(turn); // The sphinx that corresponds with the turn number will fire it's laser. (They always fire at the end of a players turn
//
//		updateBoard;
//
//		if (!(Pharaoh1.destroyed && Pharaoh2.destroyed))  // if both are alive keep playing
//		{
//			switch (turn)
//			{
//			case 1:
//				turn = 2;
//				break;
//			case 2:
//				turn = 1;
//				break;
//			}
//		}
//		else  // if one of the pharoahs is dead
//		{
//			if (Pharoah1.destroyed)
//			{
//				showWinner(2); // just prints who won the game,
//				
//				(wait for input); // Should display options to "Return to main menu" or "Quit" OR... we could just force return to main menu.
//				if (input == menu)
//					gamestate = 0;
//				else
//					gamestate = -1
//					programIsRunning = false;
//
//			}
//			else
//			{
//				showWinner(1); // just prints who won the game,
//
//				(wait for input); // Should display options to "Return to main menu" or "Quit" OR... we could just force return to main menu.
//				if (input == menu)
//					gamestate = 0;
//				else
//					gamestate = -1
//					programIsRunning = false;
//			}
//		}
//	} // IN GAME closed.
//
//
//	// HOW TO PLAY MENU
//	while (gamestate == 2)
//	{
//		displayInstructions();
//		(wait for input);
//		//Go back to menu  >> gamestate = 0;
//		//or if we have multiple pages of instructions >> Be able to iterate through them. (probably not)
//
//
//	}
//	// HOW TO PLAY MENU closed.
//
//	//OPTIONS
//	while (gamestate == 3)
//	{
//		//Probably won't get this far YEET
//	}
//
//
//}