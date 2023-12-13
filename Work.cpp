#include<iostream>
#include<vector>
#include <fstream>
#include<string>
#include<stack>
#include <queue>
#include <climits>

using namespace std ;
struct path{
	int weight ;
	int destination ;
};

struct info{
	string name ;
	vector<path> p ;
};
vector<info> Vlist ;

class DFS{
	vector<int> ans ;
	public:
		void dfs() {
			int vertices = Vlist.size() ;
		    vector<bool> visited(vertices, false) ;
		    stack<int> stack;
		
		    visited[0] = true;
		    stack.push(0);
			
		    while (!stack.empty()) {
		        int currentVertex = stack.top() ;
		        ans.push_back(currentVertex) ;
		        stack.pop() ;
					
		        for ( int i = 0 ; i < Vlist[currentVertex].p.size() ; i++ ) {
		        	int adjacentVertex = Vlist[currentVertex].p[i].destination ;
		        	//cout << Vlist[currentVertex].p[i].destination << endl;
		            if ( !visited[adjacentVertex] ) {
		                visited[adjacentVertex] = true ;
		                stack.push(adjacentVertex) ;
		            } // if
		        } // for
		    } // while
		    
		} // dfs
		
		void Main(){
			dfs() ;
			Display() ;
		} // Main()
		
		void Display(){
			cout << endl << "DFS: " << endl ;
			//cout << ans.size() << endl ;
			for( int i = 0 ; i < ans.size() ; i++ ){
				if( i == 0 ) cout << "S " ;
				else if( ans[i] == ans.size()-1 ) cout << ">> D " ;
				else cout << ">> V" << ans[i] << " " ;
			} // for
			
			cout << endl << endl ;
		} // Display()
};

class DJK{
	vector<int> ShortestPath ;
	public:
		vector<int> dijkstra() {
		    int numVertices = Vlist.size();
		    vector<int> distance(numVertices, INT_MAX);  // 記錄從起點到每個節點的距離
		    vector<bool> visited(numVertices, false);     // 記錄節點是否已訪問
		
		    distance[0] = 0;  // 從起點到自己的距離為0
		
		    // 使用最小堆來找到距離最小的節點
		    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
		    pq.push({0, 0}); //{ 節點距離，節點編號 } 
		
		    while (!pq.empty()) {
		        int current = pq.top().second;
		        pq.pop();
		
		        if (visited[current]) continue ;
		
		        visited[current] = true;
		
		        for( int i = 0 ; i < Vlist[current].p.size() ; i++ ) {
		            int neighbor = Vlist[current].p[i].destination;
		            int weight = Vlist[current].p[i].weight;
		
		            // 如果通過當前節點到達鄰居更近，則更新距離
		            if(distance[current] != INT_MAX && distance[current] + weight < distance[neighbor]) {
		                distance[neighbor] = distance[current] + weight;
		                pq.push({distance[neighbor], neighbor});
		            } // if
		        } // for
		    } // while
		
		    return distance;
		} // dijkstra
		
		void Main(){
			ShortestPath = dijkstra() ;
			Display() ;
		} // Main()
		
		void Display(){
			cout << endl << "DIJKSTRA: " << endl ;
			for( int i = 0 ;  i < ShortestPath.size() ; i++ ){
				if( i == 0 )
					cout << "Shortest distance from node S" << " to node S" << " = " << ShortestPath[i] << endl;
				else if( i == Vlist.size() - 1 )
					cout << "Shortest distance from node S" << " to node D" << " = " << ShortestPath[i] << endl;
				else 
					cout << "Shortest distance from node S" << " to node V" << i << " = " << ShortestPath[i] << endl;
			} // for
			
			cout << endl ;
		} // Display
};


vector<vector<string> > workspace ;
class Run{
	vector<string> Vinfo ;
	//vector<vector<string> > workspace ;
	public:
		bool ReadFile( string name ){
			string file = name + ".txt" ;
			fstream infile(file.c_str()) ;
			//infile.open(file.c_str(), ios::in) ;
			string temp ;
			if( !infile.is_open() ){
				cout << "### " << file << " does not exist! ### " << endl << endl ;
            	return false ;
			} // if
			else{
				int time = 0 ;				
				while( getline(infile,temp) ) {
					string currentInstance = "";
					if( temp[0] == 'I' ){
						//currentInstance = temp.substr(9, temp.find(' ', 9) - 9) ;
						info information ;
						for( int i = 9 ; i < temp.length() ; i++ ){
							//cout << "---------------" << temp.length() << endl ; 
							if( temp[i] == ' ' || temp[i] == '\t' ){
								if( currentInstance == "" ) ;
								else information.name = currentInstance, i = temp.length() ;
							} // if
							else currentInstance = currentInstance + temp[i] ;
						} // for
						
						Vlist.push_back(information) ;
					} // if
					else if ( temp[0] == 'C' || temp[0] == 'E' ) ; 
					else Vinfo.push_back(temp) ;
						
					time++ ;
				} // while
				
				/*
				for( int i = 0 ; i < Vlist.size() ; i++ ){
					cout << i << "--------------------" << Vinfo[i] << endl ;
				} // for
				*/
			} // else
			
			infile.close() ;
			return true ;
		} // Read()
		
		int Main(){
			
			string FileName ;
			cout << "Please enter your file name: (if filename is 0: quit) " << endl ;
			cin >> FileName ;
			while( FileName != "0" ){
				if( !ReadFile(FileName) ) ;
				else{
					Split() ;
					Build() ;
					Sort() ;
					
					string mode = "" ;
					
					while( mode != "0" ){
						cout << "**************************" << endl ;
						cout << "*1.DFS********************" << endl ;
						cout << "*2.DIJKSTRA***************" << endl ;
						cout << "**************************" << endl ;
						cout << "Please chose your mode: (if mode is 0:quit, 1:DFS, 2:DIJKSTRA): " << endl ;
						cin >> mode ;
						
						if( mode == "1" ){
							DFS d ;
							d.Main() ;	
						} // if
						else if( mode == "2" ){
							DJK dd ;
							dd.Main() ;
						} // else if
						else if( mode == "0" ) ;
						else cout << "Incorrect command!!!!!" << endl ;
							
							
					} // while
				} // else
				
				
				cout << "Please enter your file name: (if filename is 0->quit) " << endl ;
				cin >> FileName ;
			} // while
			
			
			/*
			string FileName  = "input";
			ReadFile(FileName) ;
			Split() ;
			Build() ;
			Sort() ;
			*/
			
			
			
		} // Main 
		
		void Split(){
			for( int i = 0 ; i < Vinfo.size() ; i++ ) {
				char pattern = ' ' ;
				string sen ;
				vector<string> Collect ;
				for( int j = 0 ; j < Vinfo[i].length() ; j++ ){
					if( Vinfo[i][j] == ' ' || Vinfo[i][j] == '\n' ){
						if( sen == "" ) ;
						else{
							Collect.push_back(sen)	 ;						
							sen = "" ;	
						} // else
						
					} // if
					else sen = sen + Vinfo[i][j] ;
				} // for
				
				if( sen != "" ) Collect.push_back(sen) ;
				workspace.push_back(Collect) ;
				
			} // for
			
			/*
			for( int i = 0 ; i < workspace.size() ; i++ ){
				cout << i << "--------------" << endl ;
				for( int j = 0 ; j < workspace[i].size() ; j++ ) {
					cout << j << "~~~~~~~~~~~~" << workspace[i][j] << endl;
				} // for
			} // for
			*/
		} // Split()
		
		void Build(){
			for( int i = 0 ; i < workspace.size() ; i++ ){
				//cout << i << "--------------" << endl ;
				for( int j = 0 ; j < workspace[i].size() ; j++ ) {
					//cout << j << "~~~~~~~~~~~~" << workspace[i][j] << endl ;
					string tt = workspace[i][j] ;
					char IO ;
					for( int k = 0 ; k < tt.length() ; k++ ){
						if( tt[k] == ')' ) IO = tt[k-1], k = tt.length() ;
					} // for
					
					// cout << j << "------------------" << tt << endl ;
					// cout << j << "~~~~~~~~~~~~~~~~~~" << IO << endl ;
					
					if( IO == 'o' ){
						string num = "", name = "" ;
						bool record = false, Nrecord = false ;
						for( int k = 0 ; k < tt.length() ; k++ ){
							if( tt[k] == '(' ) record = true ;
							else if( tt[k] == ',' ) record = false, k = tt.length() ;
							
							if( record && tt[k] != '(' ) num = num + tt[k] ;
							
							if( tt[k] == 'N' ) Nrecord = true ;
							else if( tt[k] == '(' ) Nrecord = false ;
							
							if( Nrecord ) name = name + tt[k] ;
						} // for
						
						int weight = STOI(num) ;
						
						int dest = Find(name) ;
						//cout << name << "****************" << weight << "*****************" << dest << endl ;	
						AddEdge(i, dest, weight ) ;
					} // if 
					
				} // for
			} // for
		} // Build()
		
		int STOI( string num ){
			int result = 0 ;
			for( int i = 0 ; i < num.size() ; i++ ){
				if( num[i] >= '0' && num[i] <= '9' ) result = result*10 + ( num[i] - '0' ) ;
			} // for
			
			return result ;
		}
		
		int Find( string NAME ){
			for( int i = 0 ; i < workspace.size() ; i++ ){
				for( int j = 0 ; j < workspace[i].size() ; j++ ) {
					string tt = workspace[i][j] ;
					char IO = tt[tt.length()-2] ;
					string name = "" ;
					bool record = false, Nrecord = false ;
					for( int k = 0 ; k < tt.length() ; k++ ){
						if( tt[k] == 'N' ) Nrecord = true ;
						else if( tt[k] == '(' ) Nrecord = false ;
						
						if( Nrecord ) name = name + tt[k] ;
					} // for
					
					if( NAME == name && IO == 'i' ) return i ;
				} // for
			} // for
		} // Find()
		
		void AddEdge( int start, int dest, int weight ){
			path pp ;
			pp.destination = dest ;
			pp.weight = weight ;
			Vlist[start].p.push_back(pp) ;
		} // AddEdge
		
		void Sort(){
			for( int i = 0 ; i < Vlist.size() ; i++ ){
				for( int j = 0 ; j < Vlist[i].p.size() ; j++ ){
					 
					for( int index = 0 ; index < Vlist[i].p.size()-1 ; index++ ){ //最後面不用檢查，因為一定是最大，所以每一次檢查的次數減少。 
						if( Vlist[i].p[index].weight > Vlist[i].p[index+1].weight )
							swap( index, index+1, i );
						else if( Vlist[i].p[index].destination < Vlist[i].p[index+1].destination )
							swap( index, index+1, i );
					}// for
					
				} // for
			} // for
		} // Sort
		
		void swap( int num1, int num2, int pos ){
			path p ;
			p = Vlist[pos].p[num1] ;
			Vlist[pos].p[num1] = Vlist[pos].p[num2] ;
			Vlist[pos].p[num2] = p ;
		} // swap
		
		void Display(){
			for( int i = 0 ; i < Vlist.size() ; i++ ){
				cout << Vlist[i].name << endl ;
				for( int j = 0 ; j < Vlist[i].p.size() ; j++ ){
					cout << "DEST: " << Vlist[i].p[j].destination << " " << "WEIGHT: " << Vlist[i].p[j].weight << endl;
				} // for
			} // for
		}
		
};


int main(){
	Run r ;
	r.Main() ;
	//r.Display() ;

}

