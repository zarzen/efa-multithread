#include <iostream>

#include <rdma/fabric.h>
#include <rdma/fi_cm.h>
#include <rdma/fi_domain.h>
#include <rdma/fi_endpoint.h>
#include <cstring>
#include <thread>
#include <vector>

void epThdFun() {
  struct fi_info* fi;
  struct fi_info* hints;
  struct fid_fabric* fabric;
  struct fid_domain* domain;

  struct fi_cq_attr txcq_attr, rxcq_attr;
  struct fi_av_attr av_attr;
  int err;
  std::string provider = "efa";

  hints = fi_allocinfo();
  if (!hints)
    std::cerr << "fi_allocinfo err " << -ENOMEM << "\n";

  // clear all buffers
  memset(&txcq_attr, 0, sizeof(txcq_attr));
  memset(&rxcq_attr, 0, sizeof(rxcq_attr));
  memset(&av_attr, 0, sizeof(av_attr));

  // get provider
  hints->ep_attr->type = FI_EP_RDM;
  hints->fabric_attr->prov_name = strdup(provider.c_str());
  // SAS
  hints->rx_attr->msg_order = FI_ORDER_SAS;
  hints->tx_attr->msg_order = FI_ORDER_SAS;
  err = fi_getinfo(FI_VERSION(1, 9), NULL, NULL, 0, hints, &fi);
  if (err < 0)
    std::cerr << "fi_getinfo err " << err << "\n";

  printf("fi_getinfo DONE\n");
};

int main(int argc, char const* argv[]) {
  int nthd = 4;
  std::vector<std::thread> epThds;
  for (int i = 0; i < nthd; i++){
    std::thread wt(epThdFun);
    epThds.push_back(std::move(wt));
  }

  for (int i = 0; i < nthd; i++) {
    epThds[i].join();
  }
  return 0;
}
