#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;
	int i;
	ScoreNode *p;
	initscr();
	noecho();
	keypad(stdscr, TRUE);	
	createRankList();
	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
	p = ScoreList;
	while (p!= NULL) {
		ScoreList = p->next;
		free(p);
		p = ScoreList;
	}
	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	//DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawBlocksWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	/* next next block을 보여주는 공간의 태두리를 그린다.*/
	move(9,WIDTH+10);
	printw("NEXT NEXT BLOCK");
	DrawBox(10,WIDTH+10,4,8);
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(17,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
	move(HEIGHT,WIDTH+10);
}


void PrintScore(int score){
	move(18,WIDTH+11);
	printw("%8d",score);
	move(HEIGHT,WIDTH+10);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for( i = 0; i < 4; i++ ){
		move(11+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[2]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;
	for (i = 0; i < BLOCK_HEIGHT; i++){
		for (j = 0; j < BLOCK_WIDTH; j++){
			if (block[currentBlock][blockRotate][i][j] == 1){
				if (field[i+blockY][j+blockX] == 1){  // 1) 블록을 놓으려고 하는 필드에 이미 블록이 쌓여져 있는지 여부
					return 0;
				}
				else if ((i+blockY) >= HEIGHT){       // 2) 블록을 나타내는 4×4 행렬의 각 요소의 실제 필드상의 y 좌표가 HEIGHT보다 크거나 같은지 여부
					return 0;
				}
				else if ((j+blockX) < 0){             // 3) 블록을 나타내는 4×4 행렬의 각 요소의 실제 필드상의 x 좌표가 0보다 작은지 여부
					return 0;
				}
				else if ((j+blockX) >= WIDTH){        // 4) 블록을 나타내는 4×4 행렬의 각 요소의 실제 필드상의 x 좌표가 WIDTH보다 크거나 같은지 여부
					return 0;
				}
			}
		}
	}
	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;

	switch(command){     // 1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
		case KEY_UP:
				blockRotate=(blockRotate+3)%4;
			break;
		case KEY_DOWN:
				blockY--;
			break;
		case KEY_RIGHT:
				blockX--;
			break;
		case KEY_LEFT:
				blockX++;
			break;
		default:
			break;
	}

	for (i = 0; i < BLOCK_HEIGHT; i++){  // 2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
		for (j = 0; j < BLOCK_WIDTH; j++){
			if (block[currentBlock][blockRotate][i][j] == 1 && blockY+i >= 0){
				move(i+blockY+1, j+blockX+1);
				printw(".");
			}
		}
	}

	switch(command){    // 3. 새로운 블록 정보를 그린다. 
		case KEY_UP:
				blockRotate=(blockRotate+1)%4;
			break;
		case KEY_DOWN:
				blockY++;
			break;
		case KEY_RIGHT:
				blockX++;
			break;
		case KEY_LEFT:
				blockX--;
			break;
		default:
			break;
	}
	// DrawBlock(blockY, blockX, currentBlock, blockRotate, ' ');
	DrawField();
	DrawBlocksWithFeatures (blockY, blockX, currentBlock, blockRotate);
}

void BlockDown(int sig){

	if (CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX) == 1){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else {
		if (blockY == -1){
			gameOver = 1;
		}
		
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX); // touched * 10
		
		score += DeleteLine(field);                                // deleted line^2
		nextBlock[0] = nextBlock[1];                               // Set NextBlock
		nextBlock[1] = nextBlock[2];
 		nextBlock[2] = rand()%7;
		DrawNextBlock(nextBlock);                                  // Apply changes of the nextBlock Box

		blockX = WIDTH/2 -2;                                       // Initialize the Location of currentBlock
		blockY = -1; 
		blockRotate = 0;

		DrawField();                                               // Apply changes of the field (Deleteline)
		//DrawBlock(blockY, blockX, nextBlock[0], blockRotate, ' ');
		DrawBlocksWithFeatures (blockY, blockX, nextBlock[0], blockRotate);  // To reduce the delay when block first appears
		PrintScore(score);                                         // Apply changes of the score
		move(HEIGHT,WIDTH+10);                                     // move cursor to not cover other display
	}
	timed_out = 0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j, touched;
	touched = 0;
	for (i = 0; i < BLOCK_HEIGHT; i++){
		for (j = 0; j < BLOCK_WIDTH; j++){
			if (block[currentBlock][blockRotate][i][j] == 1){
				f[blockY+i][blockX+j] = 1;
				if (f[blockY+i+1][blockX+j]==1||blockY+i+1==HEIGHT) {
					touched++;
				}
			}
		}
	}
	return touched*10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	int i, j, k , l, scr = 0, fullFlag = 0;
	for (i = 0; i < HEIGHT; i++){
		for (j = 0; j < WIDTH; j++){ // 1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
			if (f[i][j] == 0){
				fullFlag = 0;
				break;
			}
			else if (f[i][j] == 1){
				fullFlag = 1;
			}
		}
		if (fullFlag == 1){ //2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
			for (k = i; k > 0 ; k--){
				for (l = 0; l < WIDTH; l++){
					f[k][l] = f[k-1][l];
				}
			}
			scr += 1;         // 1 per pop
		}
		fullFlag = 0;
	}
	return scr*scr * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	int endY;
	endY = y;
	while (endY < HEIGHT && CheckToMove(field, blockID, blockRotate, endY+1, x) == 1){
		endY++;
	}
	DrawBlock(endY, x, blockID, blockRotate, '/');
}

void DrawBlocksWithFeatures (int y, int x, int blockID, int blockRotate) {
	DrawShadow(y,x,blockID,blockRotate);
	DrawBlock(y,x,blockID,blockRotate,' ');
}

///////////////////////////////////////////////////////////////////////////

void createRankList(){
	FILE *fp;
	ScoreNode *current;
	ScoreNode *temp;
	int i;

	current = NULL;

	fp = fopen("rank.txt", "r");
	if (fp == NULL) {
		fp = fopen("rank.txt", "w"); // 새 파일 생성
		fputc('0', fp);
		ScoreList = NULL;
		fclose(fp);
		return;
	}

	fscanf(fp, "%d", &ScoreListLength);


	for (i = 0; i < ScoreListLength; i++) {
		temp = (ScoreNode *) malloc (sizeof(ScoreNode));
		fscanf(fp, "%s\t%d", &temp->name, &temp->score);
		temp->next = NULL;

		if (current == NULL) {
			current = temp;
			ScoreList = temp;
		}
		else {
			current->next = temp;
			current = current->next;
		}	
	}

	fclose (fp);
	return;
}

void rank(){
	int back = 0;
	int foundflag = 0;
	int freedflag = 0;
	int X, Y, i, eraseRank;
	char name[NAMELEN];
	ScoreNode *current;
	ScoreNode *temp;
	current = ScoreList;
	clear();
	printw("1. List ranks from X to Y\n");
	printw("2. List ranks by a specific name\n");
	printw("3. Delete a specific rank X\n");
	printw("4. Back\n");
	
	while(!back){
		switch(wgetch(stdscr)){
		case '1':
			current = ScoreList;
			echo();
			printw("Enter rank you want to see\nX : ");
			if (scanw("%d", &X) == -1) {
				X = 1;
			}
			printw("Y : ");
			if (scanw("%d", &Y) == -1) {
				Y = ScoreListLength;
			}
			noecho();
			if (X > ScoreListLength || Y > ScoreListLength || X > Y || X <= 0 || Y <= 0) {
				printw("search failure: no rank in the list\n");
				break;
			}
			printw("\tName\t|\tScore\n");
			printw("-------------------------------------\n");
			for (i = 1; i < X; i++){
				current = current->next;
			}
			for (i=X; i<=Y; i++) {
				printw("%s\t\t|%d\n", current->name, current->score);
				current = current->next;
			}
			break;
		case '2':
			current = ScoreList;
			echo();
			printw("Enter the Name : ");
			scanw("%s", &name);
			noecho();
			for (i = 0; i < ScoreListLength; i++) {
				if (strcmp(name, current->name) == 0){
					if (foundflag == 0){
						foundflag = 1;
						printw("\tName\t|\tScore\n");
						printw("-------------------------------------\n");
					}
					printw("%s\t\t|%d\n", current->name, current->score);
				}
				current = current->next;
			}
			if (foundflag == 0){
				printw("search failure: the rank not in the list\n");
			}
			foundflag = 0;
			break;
		case '3':
			current = ScoreList;
			echo();
			printw("Enter the Rank Num to Erase : ");
			scanw("%d", &eraseRank);
			noecho();
			if (eraseRank <= 0 || eraseRank > ScoreListLength || ScoreListLength == 0){
				printw("search failure: the rank not in the list\n");
				break;
			}
			if (eraseRank == 1){
					temp = current;
					ScoreList = current->next;
					free(temp);
					freedflag = 1;
				}
			else {
				for (i = 1; i < eraseRank-1; i++) {
					current= current->next;
				}
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				freedflag = 1;
			}
			
			if (freedflag == 1){
				printw("Result: the Rank is deleted\n");
				ScoreModifiedFlag = 1;
				ScoreListLength--;
				writeRankFile();
			}
			break;			
		case '4': back=1; break;
		default: break;
		}
	}	
}

void writeRankFile(){
	FILE *fp;
	int i;
	ScoreNode *current;

	current = ScoreList;
	if (ScoreModifiedFlag == 0) {
		return;
	}
	else {
		fp = fopen("rank.txt", "w");
		fprintf(fp, "%d\n", ScoreListLength);
		for (i=0; i<ScoreListLength; i++) {
			fprintf(fp, "%s\t%d\n", current->name, current->score);
			current = current->next;
		}
	}
	fclose(fp);
	return;
}

void newRank(int score){
	ScoreNode *current, *front, *back;
	ScoreNode *temp;
	int i;

	temp = (ScoreNode *) malloc (sizeof(ScoreNode));
	temp->score = score;
	temp->next = NULL;
	clear();
	echo();
	printw("Score: %d\nEnter Your Name : ", score);
	scanw("%s", &temp->name);
	noecho();

	if (ScoreList == NULL) {
		ScoreList = temp;
	}
	else {
		current = ScoreList;
		for (i = 0; i < ScoreListLength; i++) {
			if (current->next == NULL) {
				current->next = temp;
				break;
			}
			else if (ScoreList->score <= score) {
				temp->next = ScoreList;
				ScoreList = temp;
				break;
			}
			else if (current->score >= score && score >= current->next->score) {
				front = current;
				back = current->next;
				front->next = temp;
				temp->next = back;
				break;
			}
			current = current->next;
		}
	}

	ScoreModifiedFlag = 1;
	ScoreListLength++;
	writeRankFile();
}

///////////////////////////////////////////////////////////////////////////

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}
