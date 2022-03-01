#pragma once
#include <ros/ros.h>

#include <kimera_dsg/dynamic_scene_graph.h>
#include <pcl/PolygonMesh.h>
#include <voxblox/integrator/esdf_integrator.h>

namespace kimera {

namespace utils {

struct VoxbloxConfig {
  voxblox::EsdfIntegrator::Config esdf_config;
  std::string tsdf_file;
  std::string esdf_file;
  std::string mesh_file;
  std::string gvd_namespace;
  bool load_places = false;
  bool load_esdf;
  bool load_mesh;
  double voxel_size;
  size_t voxels_per_side;
};

std::optional<VoxbloxConfig> loadVoxbloxConfig(const ros::NodeHandle& nh);

void makeMeshFromTsdf(const voxblox::Layer<voxblox::TsdfVoxel>& tsdf,
                      pcl::PolygonMesh::Ptr& mesh,
                      ros::Publisher* mesh_pub);

bool loadVoxbloxInfo(const VoxbloxConfig& config,
                     voxblox::Layer<voxblox::EsdfVoxel>::Ptr& esdf,
                     pcl::PolygonMesh::Ptr& mesh,
                     ros::Publisher* mesh_pub = nullptr,
                     DynamicSceneGraph* graph = nullptr);

bool updateFromTsdf(const VoxbloxConfig& config,
                    voxblox::Layer<voxblox::TsdfVoxel>& tsdf,
                    voxblox::Layer<voxblox::EsdfVoxel>::Ptr& esdf,
                    pcl::PolygonMesh::Ptr& mesh,
                    DynamicSceneGraph* graph);

}  // namespace utils

}  // namespace kimera
