#include <ATen/ATen.h>
namespace at { namespace native {

std::vector<Tensor> foreach_add_scalar_kernel_fallback(TensorList tensors, Scalar scalar) {
  TORCH_CHECK(tensors.size() > 0, "Tensor list must have at least one tensor.");

  std::vector<Tensor> result;
  for (int i = 0; i < tensors.size(); i++) {
    auto temp = tensors[i].add(scalar);
    result.emplace_back(temp);
  }
  return result;
}

std::vector<Tensor> foreach_add_scalar__kernel_cpu(TensorList tensors, Scalar scalar) {
  TORCH_CHECK(tensors.size() > 0, "Tensor list must have at least one tensor.");

  for (int i = 0; i < tensors.size(); i++) {
    tensors[i].add_(scalar);
  }

  return tensors.vec();
}

std::vector<Tensor> foreach_add_list_kernel_cpu(TensorList tensors1, TensorList tensors2) {
  TORCH_CHECK(tensors1.size() > 0, "Tensor list must have at least one tensor.");
  TORCH_CHECK(tensors1.size() ==  tensors2.size(), "Tensor lists must be of the same length.");

  std::vector<Tensor> result;
  for (int i = 0; i < tensors1.size(); i++) {
    auto temp = tensors1[i].add(tensors2[i]);
    result.emplace_back(temp);
  }
  return result;
}

std::vector<Tensor> foreach_add_list__kernel_cpu(TensorList tensors1, TensorList tensors2) {
  TORCH_CHECK(tensors1.size() > 0, "Tensor list must have at least one tensor.");
  TORCH_CHECK(tensors1.size() ==  tensors2.size(), "Tensor lists must be of the same length.");

  for (int i = 0; i < tensors1.size(); i++) {
    tensors1[i].add_(tensors2[i]);
  }
  return tensors1.vec();
}

}} // namespace at::native