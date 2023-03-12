#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>

//Quick Union Algorithm

int root(int r, std::vector<std::vector<int>> id){
  while(id[r][0] !=r){
   r = id[r][0]; 
  }
  return r;
}

bool connected(int p, int q, std::vector<std::vector<int>> id){
  return root(p, id) == root(q, id);
}

void UNION(int p, int q, std::vector<std::vector<int>>& id){
  int i = root(p,id);
  int j = root(q,id);
  
  id[i][0] = j;
}






//Grid and Opening

std::vector<std::vector<int>> grid(int N){
  std::vector<std::vector<int>> id;
  for(int i=0; i<N*N+2; i++){
    std::vector<int> cell;
    cell.push_back(i);
    cell.push_back(0);
    id.push_back(cell);
    }
  return id;
  }

std::vector<int> deckler(int N){
  std::vector<int> shuffle;
  for(int i=1; i < N*N+1; i++){
    shuffle.push_back(i);
  }
  return shuffle;
}

void gridGen(int N, std::vector<std::vector<int>> id){
  int cnt = 0;
  for(int i=1; i<id.size()-1; i++){
    if(id[i][1] == 0){
      std::cout << "⬛ ";
    }else if((id[i][1] == 1) && (connected(i, 0, id))){
      std::cout << "💦 ";
    }else{
      std::cout << "⬜ ";
    }
    cnt += 1;
    if(cnt%N == 0){
      std::cout << std::endl;
      cnt = 0;
    }
  }
  std::cout << std::endl;
}


int randGen(int N, std::vector<int>& deck){
  std::random_shuffle(deck.begin(), deck.end());
  //for(int i=0; i<deck.size(); i++){
  //std::cout << i << ": " << deck[i] << std::endl;
    //}
  int returnVal = deck[0];
  deck.erase(deck.begin());
  return returnVal;
}

void unionSurr(int N, int p, std::vector<std::vector<int>>& id){
  //corners
  if(p == 1){
    if(id[p+N][1] == 1){
    UNION(1, p+N, id);
      }
  }else if(p == N){
    if(id[p+N][1] == 1){
    UNION(p, p+N, id);
      }
  }else if(p == N*(N-1)+1){
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
  }else if(p == N*N){
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
  //top and bottom sides
  }else if((p>1) && (p<N)){
    if(id[p+N][1] == 1){
    UNION(p, p+N, id);
      }
  }else if((p>N*(N-1)+1) && (p<N*N)){
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
  //left and right sides
  }else if((p-1)%N == 0){
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
    if(id[p+1][1] == 1){
    UNION(p, p+1, id);
      }
    if(id[p+N][1] == 1){
    UNION(p, p+N, id);
      }
  }else if(p%N == 0){
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
    if(id[p-1][1] == 1){
    UNION(p, p-1, id);
      }
    if(id[p+N][1] == 1){
    UNION(p, p+N, id);
      }
  //centre
  }else{
    if(id[p-N][1] == 1){
    UNION(p, p-N, id);
      }
    if(id[p-1][1] == 1){
    UNION(p, p-1, id);
      }
    if(id[p+N][1] == 1){
    UNION(p, p+N, id);
      }
    if(id[p+1][1] == 1){
    UNION(p, p+1, id);
      }
  }
}

void cellOpenerAndConn(int N, std::vector<std::vector<int>>& id, std::vector<int>& deck){
  int randCell = randGen(N, deck);
  id[randCell][1] = 1;
  unionSurr(N, randCell, id);
}

void CHEATcellOpenerAndConn(int N, std::vector<std::vector<int>>& id, int p){
  id[p][1] = 1;
  unionSurr(N, p, id);
}

void unionInit(int N, std::vector<std::vector<int>>& id){
  for(int i=1; i<N+1; i++){
    UNION(i, 0, id);
    UNION(N*N-N+i, N*N+1, id);
  }

}



int main() {
  int N = 25;
  std::vector<std::vector<int>> id = grid(N);
  std::vector<int> deck = deckler(N);
  unionInit(N, id);
  
  //cellOpenerAndConn(N, id, deck);

 while(connected(0, N*N+1, id) != 1){
   cellOpenerAndConn(N, id, deck);
   gridGen(N, id);
 } 
int counter = 0;
  for(int i=1; i<id.size()-1; i++){
    if(id[i][1] == 1){
      counter += 1;
    }
  }
  std::cout << counter;

}
