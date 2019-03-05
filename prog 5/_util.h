
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

void show_graph(graph &g) {

  std::cout << "\n< BEGIN ADJACENCY-LIST:\n\n";
  if(g.num_nodes() <= 20) {
    g.display();
  }
  else {
    std::cout << "        [ OMITTED -- BIG GRAPH! ]\n";
  }
  std::cout << "\nEND ADJACENCY LIST >\n\n";
}



void header(int argc, char *argv[]) {

  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  std::cout << "+\n";
  std::cout << "+ THIS OUTPUT IS THE RESULT OF THE FOLLOWING COMMAND-LINE:\n+\n+    ";
  for(int i=0; i<argc; i++) {
    std::cout << argv[i] << " ";
  }
  std::cout << "\n+\n";
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}



bool name_vec2id_vec(graph &g, vector<string> &name_vec, vector<int> &id_vec) {
  int id;

  id_vec.clear();

  for(string &name : name_vec)  {
    if( (id = g.name2id(name)) == -1) 
        return false;
    id_vec.push_back(id);
  }

  return true;

}


bool file2name_vec(graph &g, const string &fname, vector<string> & str_vec) {
      std::ifstream file;
      string name;

      str_vec.clear();
      file.open(fname, std::ios::in);
      if(!file.is_open())
        return false;

      file >> name;
      while(file.good()) {
        if(g.name2id(name) == -1){
          std::cerr << "ERR: file2name_vec(): no such vertex as '" << name << "'\n";
          file.close();
          return false;
        }
        str_vec.push_back(name);
        file >> name;
      }
      file.close();

      return true;
}


/**
* interprets contents of given file as a sequence of vertex-names in graph g.
*
* Result:  populates id_vec with corresponding vertex IDs in the same order
*   presented in file.
*
* failure conditions (false returned):  
*
*    if file cannot be opened
*
*    if any of the "tokens" in the input file do not match any vertes name in g
*/
bool file2id_vec(graph &g, const string &fname, vector<int> & id_vec) {

  vector<string> names;

  if(!file2name_vec(g, fname, names))
    return false;


  return name_vec2id_vec(g, names, id_vec);
}


