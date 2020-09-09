#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

struct cell{
    int x;
    int y;
    unsigned int time=0;
};

class bfs_tree{
public:
    bfs_tree(int **map, int X, int Y, cell start1, cell start2){
        this->map = map;
        this->X = X;
        this->Y = Y;
        this->start1 = start1;
        this->start2 = start2;
    }

    void two_way_bfs(cell curr_cell1, cell curr_cell2){

        int x1 = curr_cell1.x;
        int y1 = curr_cell1.y;
        int x2 = curr_cell2.x;
        int y2 = curr_cell2.y;

        rob1.push_back(curr_cell1);
        rob2.push_back(curr_cell2);

        int ret1=-1;
        int ret2=-1;

        while ( rob1.empty() == false && rob2.empty() == false ){
        	
        	cout << "stack 1 :";
        	for (auto i: rob1){
        		cout << i.x  << " " << i.y << endl;
			}
			cout << endl;
			cout << "stack 2 :";
        	for (auto i: rob2){
        		cout << i.x  << " " << i.y << endl;
			}
			cout << endl;
            
            ret1 = push_to_bfs_stack(rob1, rob1[0], 2, 3);
            if (ret1 != -1){
                cout << "Answer :" << ret1 << endl;
                break;
            }
            ret2 = push_to_bfs_stack(rob2, rob2[0], 3, 2);
            if (ret2 != -1){
                cout << "Answer :" << ret2 << endl;
                break;
            }

            rob1.erase( rob1.begin() );
            rob2.erase( rob2.begin() );

        }

        for (int i=0; i<Y; i++){
			for (int j=0; j<X; j++){
				cout << map[i][j] << " ";
			}
			cout << endl;
		}

    }

    int push_to_bfs_stack( vector<cell>& stck, cell _cell , int rob_no, int opp_rob_no){
        cell tmp;
        int ret=-1;
        int x = _cell.x;
        int y = _cell.y;
        do{
            if ( y - 1 >= 0 ){
                if ( map[ y-1 ][x] != 1 ){
                    if ( map[y-1][x] == 0 ){
                        tmp.x = x;
                        tmp.y = y-1;
                        tmp.time = _cell.time + 1;
                        stck.push_back(tmp);
                        map[y-1][x] = rob_no;
                    }else if ( map [y-1][x] == opp_rob_no){
                        cout << "Soulution found" << endl;
                        ret = _cell.time + 1;
                        break;
                    }
                }
            }
            if ( x - 1 >=0 ){
                if ( map[ y ][x-1] != 1 ){
                    if ( map[y][x-1] == 0 ){
                        tmp.x = x-1;
                        tmp.y = y;
                        tmp.time = _cell.time + 1;
                        stck.push_back(tmp);
                        map[y][x-1] = rob_no;
                    }else if ( map [y][x-1] == opp_rob_no){
                        cout << "Soulution found" << endl;
                        ret = _cell.time + 1;
                        break;
                    }
                }
                
            }
            if ( y + 1 <= Y-1){
                if ( map[ y+1 ][x] != 1 ){
                    if ( map[y+1][x] == 0 ){
                        tmp.x = x;
                        tmp.y = y+1;
                        tmp.time = _cell.time + 1;
                        stck.push_back(tmp);
                        map[y+1][x] = rob_no;
                    }else if ( map [y+1][x] == opp_rob_no){
                        cout << "Soulution found" << endl;
                        ret = _cell.time + 1;
                        break;
                    }
                }
            }
            if ( x + 1 <= X-1 ){
                if ( map[ y ][x+1] != 1 ){
                    if ( map[y][x+1] == 0 ){
                        tmp.x = x+1;
                        tmp.y = y;
                        tmp.time = _cell.time + 1;
                        stck.push_back(tmp);
                        map[y][x+1] = rob_no;
                    }else if ( map [y][x+1] == opp_rob_no){
                        cout << "Soulution found" << endl;
                        ret = _cell.time + 1;
                        break;
                    }
                }
            }
        }while(false);
        return ret;
    }



    int **map;
    int X;
    int Y;

    cell start1;
    cell start2;

    vector<cell>rob1;
    vector<cell>rob2;

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
	b1.two_way_bfs(rob1, rob2);

    return 0;

}
