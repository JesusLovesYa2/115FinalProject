#include"map.h"

void mapToGraph(Map m, char character, Graph* g){//The map is our blueprint, the character will determine the next function to call for edge weights,
                //and the graph is the final output.
  /*
      Monkey: M
      Bird: B
      Fish: F
      Frog: G

      '^' = high mountain
      ' ' = plain
      '"' = forest
      '.' = desert
      '~' = ocean
*/
  //Figure out what all the weights should be
      if(character == 'M'){
        //Input appropiate code
        
      }else if(character == 'B'){
        //Input appropiate code
      }else if(character == 'F'){
        //Input appropiate code
      }else if(character == 'G'){
        //Input appropiate code
      }else {
          std::cout<< "You entered an invalid character."<<std::endl;
      }
    return;
}
