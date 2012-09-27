#include "stdafx.h"
#include "Field.h"

	Field::Field(){
		width = 50;
		height = 50;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				node[i][j].setProperties('O'); 
			}
		}
	}
	Field::Field(int w, int h){
		width = w;
		height = h;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				node[i][j].setProperties('O'); 
			}
		}
	}
	Field::~Field(){
	}
	void Field::setWidth(int w){
		width = w;
	}
	void Field::setHeight(int h){
		height = h;
	}
	int Field::getWidth(){
		return width;
	}
	int Field::getHeight(){
		return height;
	}

	void Field::setStartx(int s) {
		start_x = s;
	}
	void Field::setStarty(int s) {
		start_y = s;
	}
	void Field::setFinishx(int f) {
		finish_x = f;
	}
	void Field::setFinishy(int f) {
		finish_y = f;
	}
	int Field::getStartx() {
		return start_x;
	}
	int Field::getStarty() {
		return start_y;
	}
	int Field::getFinishx() {
		return finish_x;
	}
	int Field::getFinishy() {
		return finish_y;
	}

	void Field::findStartNode() {
		bool found = false;
		/* cari di kolom kiri */ 
		for (int i=0; i<50; i++){
			if (node[i][0].getProperties() == 'O') {
				setStartx(i);
				setStarty(0);
				found = true;
				break;
			}
		}
		/* cari di baris bawah */
		if (!found) {
			for (int i=0; i<50; i++){
				if (node[49][i].getProperties() == 'O') {
					setStartx(49);
					setStarty(i);
					found = true;
					break;
				}
			}
		}
		/* cari di kolom kanan */
		if (!found) {
			for (int i=0; i<50; i++){
				if (node[i][49].getProperties() == 'O') {
					setStartx(i);
					setStarty(49);
					found = true;
					break;
				}
			}
		}
		/* cari di baris atas */
		if (!found) {
			for (int i=0; i<50; i++){
				if (node[0][i].getProperties() == 'O') {
					setStartx(0);
					setStarty(i);
					found = true;
					break;
				}
			}
		}
	}

	void Field::getPath(int x, int y, int path_idx,int* path) {
		if ((node[x][y-1].getProperties() == 'O') && ((y-1) >=0) && (path[path_idx] != 2)) { //atas 
			path[path_idx + 1] = 0;
			getPath(x, y-1, path_idx+1, path);
		}
		else
		if ((node[x+1][y].getProperties() == 'O') && ((x+1) < 50) && (path[path_idx] != 3)) { //kanan
			path[path_idx + 1] = 1;
			getPath(x+1, y, path_idx+1, path);
		}
		else
		if ((node[x][y+1].getProperties() == 'O') && ((y+1) < 50) && (path[path_idx] != 0)) { //bawah 
			path[path_idx + 1] = 2;
			getPath(x, y+1, path_idx+1, path);
		}
		else
		if ((node[x-1][y].getProperties() == 'O') && ((x-1) >=0) && (path[path_idx] != 1)) { //kiri
			path[path_idx + 1] = 3; 
			getPath(x-1, y, path_idx+1, path);
		}
	}

	void Field::findFinishNode() {
		/* perlu ga ya? kyknya ngak */
	}

	/*Node Field::getNode(int i, int j){
		return node[i][j];
	}

	Node& Field::getNode2(int i, int j){
		return node[i][j];
	}*/

	void Field::Load(string inputfile){
		string line[50];
		int i, j;
		cout << "Generating map . . ." << endl;
		ifstream myfile (inputfile);
		if (myfile.is_open())
		{
			i = 0;
			while ( myfile.good() )
			{
				getline (myfile,line[i]);
				j = 0;
				while ( j < line[i].length() ) {
					node[i][j].setProperties(line[i][j]);
					cout << node[i][j].getProperties();
					j++;
				}
				cout<<endl;
				i++;
			}
		width = i;
		height = j;
		myfile.close();
		
		_image.LoadFromFile("images/terrain.png");
		//cout << "harusnya ini cuma 1x" << endl;
		_sprite.SetImage(_image);
		//_sprite.SetSubRect(sf::IntRect(currentFrame*SPRITE_WIDTH, 0, (currentFrame+1)*SPRITE_WIDTH, SPRITE_HEIGHT) );
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				switch (node[i][j].getProperties()){
					/*case 'X' :
					{
						node[i][j].Load();
						break;
					}
					case 'O' :
					{
						node[i][j].Load(); 
						break;
					}*/
					case 'S' :
					{
						//node[i][j].Load();
						Start = node[i][j];
						break;
					}
					case 'F' :
					{
						//node[i][j].Load();
						Finish = node[i][j];
						break;
					}
					default :
					{
						break;
					}

				}
				//node[i][j].GetSprite().SetPosition(j*64, i*64);
			}
		}
	}

	  else 
		  cout << "Unable to open file"; 
	}

	void Field::Draw(sf::RenderWindow & renderWindow){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				switch (node[i][j].getProperties()){
					case 'X' :
					{
						_sprite.SetSubRect(sf::IntRect(0, 0, 64, 64));
						_sprite.SetPosition(j*64, i*64);
						renderWindow.Draw(_sprite);
						//node[i][j].Draw(renderWindow);
						break;
					}
					case 'O' :
					{
						_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
						_sprite.SetPosition(j*64, i*64);
						renderWindow.Draw(_sprite);
						//node[i][j].Draw(renderWindow); 
						break;
					}
					case 'S' :
					{
						_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
						_sprite.SetPosition(j*64, i*64);
						renderWindow.Draw(_sprite);
						//node[i][j].Draw(renderWindow); 
						break;
					}
					case 'F' :
					{
						_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
						_sprite.SetPosition(j*64, i*64);
						renderWindow.Draw(_sprite);
						//node[i][j].Draw(renderWindow); 
						break;
					}
					default :
					{break;}
				}
				//{node[i][j].Draw(renderWindow); break;}
			}
		}
	}