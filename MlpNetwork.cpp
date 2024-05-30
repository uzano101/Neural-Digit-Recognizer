#include "MlpNetwork.h"
#include "Dense.h"
#include "Activation.h"
using namespace activation;
digit MlpNetwork::operator () (const Matrix& X)
{
  Dense r1(weight_mat[0], bias_mat[0], relu);
  Matrix first_layer = r1(X);
  Dense r2(weight_mat[1], bias_mat[1], relu);
  Matrix second_layer = r2(first_layer);
  Dense r3(weight_mat[2], bias_mat[2], relu);
  Matrix third_layer = r3(second_layer);
  Dense r4(weight_mat[3], bias_mat[3], softmax);
  Matrix fourth_layer = r4(third_layer);
  float max = 0;
  int index_of_max;
  for (int i = 0 ; i < fourth_layer.get_rows() ; i ++)
  {
    if (fourth_layer[i] > max)
    {
      max = fourth_layer[i];
      index_of_max = i;
    }
  }
  digit result;
  result.value = index_of_max;
  result.probability = max;
  return result;
}