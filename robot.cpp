#include <iostream>
#include <vector>
#include <iterator>

#define PATH                  0
#define WALL                  1
#define SALESMAN_1_TRAIL      2
#define SALESMAN_2_TRAIL      3

using namespace std;

struct cell{
    int x;
    int y;
    unsigned int time=0;
    cell * parent = nullptr;
};

class bfs_tree{
public:
    bfs_tree(int **map, int X, int Y, cell start, cell destination){
        this->map = map;
        this->X = X;
        this->Y = Y;
        this->start = start;
        this->destination = destination;
        map[ start.y ][start.x] = SALESMAN_1_TRAIL;
        map[ destination.y ][ destination.x ] = SALESMAN_2_TRAIL;

        map_of_parents = new int* [Y];
	    for (int i=0; i<Y; i++){
		    map_of_parents[i] = new int[X];
	    }

        for (int i=0; i<Y; i++){
            for (int j=0; j<X; j++){
                map_of_parents[i][j] = 0;
            }
        }
    }

    void optimized_bfs(){

        int x1 = start.x;
        int y1 = start.y;
        int x2 = destination.x;
        int y2 = destination.y;

        map[y1][x1] = SALESMAN_1_TRAIL;
        bfs_queue.push_back(start);

        map[y2][x2] = SALESMAN_2_TRAIL;

        int ret1=-1;

        while ( bfs_queue.empty() == false ){
        	
        	// cout << "stack 1 :";
        	// for (auto i: bfs_queue){
        	// 	cout << i.x  << "-" << i.y << endl;
			// }
			// cout << endl;
            
            ret1 = push_neighbours_to_bfs_stack(bfs_queue, bfs_queue[0]);
            if (ret1 != -1){
                print_path();
                cout << "Answer :" << ret1 << endl;
                break;
            }
            

            bfs_queue.erase( bfs_queue.begin() );

        }

        for (int i=0; i<Y; i++){
			for (int j=0; j<X; j++){
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
        cout << endl << endl;
        for (int i=0; i<Y; i++){
			for (int j=0; j<X; j++){
				cout << map_of_parents[i][j] << " ";
			}
			cout << endl;
		}

    }

    int print_path(){
        cout << "Print path called" << endl;
        int p = destination.x;
        int q = destination.y;
        while(true){
            cout << "p = " << p << " q = " << q << endl;
            if ( map_of_parents[q][p] == 0 ){
                break;
            }else{
                map[q][p] = 8;
                if ( map_of_parents[q][p] == 1 ){
                    q = q-1;
                }else if ( map_of_parents[q][p] == 2 ){
                    p = p-1;
                }else if ( map_of_parents[q][p] == 3 ){
                    q = q+1;
                }else if ( map_of_parents[q][p] == 4){
                    p = p+1;
                }
            }

        }
    }

    int push_neighbours_to_bfs_stack( vector<cell>& stck, cell _cell){
        cell tmp;
        int ret=-1;
        int x = _cell.x;
        int y = _cell.y;

        cout << "cell: (" << y << "," << x << ")" << endl;
        do{
            if ( y - 1 >= 0 ){
                if ( map[ y-1 ][x] != WALL ){
                    if ( map[y-1][x] == PATH ){
                        tmp.x = x;
                        tmp.y = y-1;
                        tmp.time = _cell.time + 1;
                        map_of_parents[tmp.y][tmp.x] = 3;
                        stck.push_back(tmp);
                        map[y-1][x] = SALESMAN_1_TRAIL;
                    }else if ( map [y-1][x] == SALESMAN_2_TRAIL){
                        cout << "Soulution found" << endl;
                        ret = _cell.time + 1;
                        map_of_parents[y-1][x] = 3;
                        break;
                    }
                }
            }
            if ( x - 1 >=0 ){
                if ( map[ y ][x-1] != WALL ){
                    if ( map[y][x-1] == PATH ){
                        tmp.x = x-1;
                        tmp.y = y;
                        tmp.time = _cell.time + 1;
                        map_of_parents[tmp.y][tmp.x] = 4;
                        stck.push_back(tmp);
                        map[y][x-1] = SALESMAN_1_TRAIL;
                    }else if ( map [y][x-1] == SALESMAN_2_TRAIL){
                        cout << "Soulution found" << endl;
                        map_of_parents[y][x-1] = 4;
                        ret = _cell.time + 1;
                        break;
                    }
                }
                
            }
            if ( y + 1 <= Y-1){
                if ( map[ y+1 ][x] != WALL ){
                    if ( map[y+1][x] == PATH ){
                        tmp.x = x;
                        tmp.y = y+1;
                        tmp.time = _cell.time + 1;
                        map_of_parents[tmp.y][tmp.x] = 1;
                        stck.push_back(tmp);
                        map[y+1][x] = SALESMAN_1_TRAIL;
                    }else if ( map [y+1][x] == SALESMAN_2_TRAIL){
                        cout << "Soulution found" << endl;
                        map_of_parents[y+1][x] = 1;
                        ret = _cell.time + 1;
                        break;
                    }
                }
            }
            if ( x + 1 <= X-1 ){
                if ( map[ y ][x+1] != WALL ){
                    if ( map[y][x+1] == PATH ){
                        tmp.x = x+1;
                        tmp.y = y;
                        tmp.time = _cell.time + 1;
                        map_of_parents[tmp.y][tmp.x] = 2;
                        stck.push_back(tmp);
                        map[y][x+1] = SALESMAN_1_TRAIL;
                    }else if ( map [y][x+1] == SALESMAN_2_TRAIL){
                        cout << "Soulution found" << endl;
                        map_of_parents[y][x+1] = 2;
                        ret = _cell.time + 1;
                        break;
                    }
                }
            }
        }while(false);
        return ret;
    }

    int **map;
    int **map_of_parents;
    int X;
    int Y;

    cell start;
    cell destination;

    vector<cell>bfs_queue;

};


int main(){
	
	int N, M;
	cin >> N >> M;

	int **map;
	map = new int* [N];
	for (int i=0; i<N; i++){
		map[i] = new int[M];
	}
	
	for (int i=0; i<N; i++){
		for (int j=0; j<M; j++){
			cin >> map[i][j];
		}
	}
	
	for (int i=0; i<N; i++){
		for (int j=0; j<M; j++){
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	
    cell rob1;
    rob1.x = 0;
    rob1.y = 0;
    rob1.time = 0;

	cell rob2;
    rob2.x = M-1;
    rob2.y = N-1;
    rob2.time = 0;
    
	bfs_tree b1 (map, M, N, rob1, rob2);
	b1.optimized_bfs();

    return 0;

}
