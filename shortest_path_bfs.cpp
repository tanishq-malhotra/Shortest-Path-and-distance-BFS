#include<bits/stdc++.h>
using namespace std;

//class used in our bfs algorithm
class sh
{
public:
	//x and y are the initial position's
	//i and j are used to store the position's of the previous cell
	int x,y,i,j,d;
	sh():x(0),y(0),i(0),j(0),d(0){}
	sh(int xx, int yy, int ii, int jj,int dd)
	{
		x=xx; y=yy; i=ii; j=jj; d=dd;
	}
};

//function which reads from the txt file and store it into char array
char **patt2grid()
{
	//allocationg memory
	char **grid = new char*[20];
	for(int i = 0; i < 20; i++) grid[i] = new char[35];
	//creating file object
	fstream file;
	//opening file
	file.open("pattern.txt");
	int i = 0;
	string line;
	//loop used to read line by line from text file
	while(getline(file,line))
	{
		//iterating through line and storing into array
		for(int k = 0; k < line.length(); k++)
			grid[i][k] = line[k];
		i += 1;
	}
	file.close();
	return grid;
}

//main function 
void shortest_path()
{
	//coordinates of the source
	int sx,sy;
	//creating grid
	char **grid = patt2grid();
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 35; j++)
		{
			if(grid[i][j] == 'O')
			{
				sx = i; sy = j;
				break;
			}
		}

	//creating initial object 
	sh s(sx,sy,sx,sy,0);
	//creating a queue to store objects
	queue<sh> q;
	//pushing the object to queue
	q.push(s);

	//creating a 2d array of objects
	sh g[20][35];

	//visited array to check the unvisited and visited sections
	bool visited[20][35];
	int a,b;

	//loop for storing the object in g and for marking visited
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 35; j++)
		{
			g[i][j] = s;
			if(grid[i][j] == '#')
				visited[i][j] = true;
			else if(grid[i][j] == 'F')
			{
				a = i; b = j; visited[i][j] = false;
			}
			else
				visited[i][j] = false;	
		}
	}
	//marking source as visited
	visited[sx][sy] = true;
	int dist,n=20,m=35;

	//main bfs algo loop
	while(!q.empty())
	{
		//creating a class object
		sh p;
		//storing the front object of queue in created object
		p = q.front();
		//poping the object from queue
		q.pop();

		//checking if we reached our destination
		if(grid[p.x][p.y] == 'F')
		{
			dist = p.d;
			break;
		}

		//moving up
		if(p.x-1 >= 0 && visited[p.x-1][p.y] == false)
		{
			//pushing into queue new object
			q.push(sh(p.x - 1 , p.y, 0,0,p.d + 1));
			//marking true in visited
			visited[p.x-1][p.y] = true;
			//storing the values of previous position in g array
			g[p.x-1][p.y].i = p.x;
			g[p.x-1][p.y].j = p.y;
		}

		//moving down
		else if(p.x + 1 < n && visited[p.x + 1][p.y] == false)
		{
			q.push(sh(p.x + 1, p.y, 0,0,p.d + 1));
			visited[p.x + 1][p.y] = true;
			g[p.x+1][p.y].i = p.x;
			g[p.x+1][p.y].j = p.y;
		}

		//moving left
		if(p.y - 1 >= 0 && visited[p.x][p.y-1] == false)
		{
			q.push(sh(p.x, p.y - 1, 0,0,p.d + 1));
			visited[p.x][p.y-1] = true;
			g[p.x][p.y-1].i = p.x;
			g[p.x][p.y-1].j = p.y;
		}

		//moving right
		if(p.y + 1 < m && visited[p.x][p.y + 1] == false)
		{
			q.push(sh(p.x,p.y + 1,0,0,p.d + 1));
			visited[p.x][p.y + 1] = true;
			g[p.x][p.y+1].i = p.x;
			g[p.x][p.y+1].j = p.y;
		}
	}
	//if dist is > 0 means we have there is a path available
	if(dist>0)
	{
	int f = 0;
	//backtracking to create the path
	while(1)
	{
		//if f is 0 means first time then F is marked
		if(f == 0)
		{
		grid[a][b] = 'F';
		f += 1;
	    }
	    else grid[a][b] = '~';
	    //changing the values of a and b to the previous posititon 
	    //stored in the i and j of the object
		a = g[a][b].i;
		b = g[a][b].j;

		//if we have reached to our source
		if(grid[a][b] == 'O') break;
	}

	//printing final path and distance
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<dist;
}
//if dist is less than 0 then no path is available
else
cout<<"no path available";
}

int main()
{
	//function called
	shortest_path();
	return 0;
}