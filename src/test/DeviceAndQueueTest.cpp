#include "DeviceAndQueueTest.h"
NS_TEST_BEGIN



//一下注释的在vulkanspecific中说明但是包含的vulkan头文件中没有申明，估计还需要包含别的头文件啥的，目前先不管
struct PhysicalDeviceProperties {
	VkPhysicalDeviceProperties2 Properties2{};//最主要的设备属性，下面的是其他的属性
	VkPhysicalDeviceAccelerationStructurePropertiesKHR AccelerationStructurePropertiesKHR{};
	VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT BlendOperationAdvancedPropertiesEXT{};
	VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI ClusterCullingShaderPropertiesHUAWEI{};
	VkPhysicalDeviceConservativeRasterizationPropertiesEXT ConservativeRasterizationPropertiesEXT{};
	//VkPhysicalDeviceCooperativeMatrixPropertiesKHR CooperativeMatrixPropertiesKHR{};
	VkPhysicalDeviceCooperativeMatrixPropertiesNV CooperativeMatrixPropertiesNV{};
	VkPhysicalDeviceCopyMemoryIndirectPropertiesNV  CopyMemoryIndirectPropertiesNV{};
	//VkPhysicalDeviceCudaKernelLaunchPropertiesNV CudaKernelLaunchPropertiesNV{};
	VkPhysicalDeviceCustomBorderColorPropertiesEXT CustomBorderColorPropertiesEXT{};
	VkPhysicalDeviceDepthStencilResolveProperties DepthStencilResolveProperties{};
	VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT DescriptorBufferDensityMapPropertiesEXT{};
	VkPhysicalDeviceDescriptorBufferPropertiesEXT DescriptorBufferPropertiesEXT{};
	VkPhysicalDeviceDescriptorIndexingProperties DescriptorIndexingProperties{};
	VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV DeviceGeneratedCommandsPropertiesNV{};
	VkPhysicalDeviceDiscardRectanglePropertiesEXT DiscardRectanglePropertiesEXT{};
	//VkPhysicalDeviceDisplacementMicromapPropertiesNV DisplacementMicromapPropertiesNV{};
	VkPhysicalDeviceDriverProperties DriverProperties{};
	VkPhysicalDeviceDrmPropertiesEXT DrmPropertiesEXT{};
	VkPhysicalDeviceExtendedDynamicState3PropertiesEXT ExtendedDynamicState3PropertiesEXT{};
	//VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV ExtendedSparseAddressSpacePropertiesNV{};
	//VkPhysicalDeviceExternalFormatResolvePropertiesANDROID ExternalFormatResolvePropertiesANDROID{};
	VkPhysicalDeviceExternalMemoryHostPropertiesEXT ExternalMemoryHostPropertiesEXT{};
	VkPhysicalDeviceFloatControlsProperties FloatControlsProperties{};
	VkPhysicalDeviceFragmentDensityMap2PropertiesEXT FragmentDensityMap2PropertiesEXT{};
	VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM FragmentDensityMapOffsetPropertiesQCOM{};
	VkPhysicalDeviceFragmentDensityMapPropertiesEXT FragmentDensityMapPropertiesEXT{};
	VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR FragmentShaderBarycentricPropertiesKHR{};
	VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV FragmentShadingRateEnumsPropertiesNV{};
	VkPhysicalDeviceFragmentShadingRatePropertiesKHR FragmentShadingRatePropertiesKHR{};
	VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT GraphicsPipelineLibraryPropertiesEXT{};
	//VkPhysicalDeviceHostImageCopyPropertiesEXT HostImageCopyPropertiesEXT{};
	VkPhysicalDeviceIDProperties IDProperties{};
	//VkPhysicalDeviceImageAlignmentControlPropertiesMESA mageAlignmentControlPropertiesMESA{};
	//VkPhysicalDeviceImageProcessing2PropertiesQCOM ImageProcessing2PropertiesQCOM{};
	VkPhysicalDeviceImageProcessingPropertiesQCOM ImageProcessingPropertiesQCOM{};
	VkPhysicalDeviceInlineUniformBlockProperties InlineUniformBlockProperties{};
	//VkPhysicalDeviceLayeredDriverPropertiesMSFT LayeredDriverPropertiesMSFT{};
	//VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT VertexAttributesPropertiesEXT{};
	//VkPhysicalDeviceLineRasterizationPropertiesKHR LineRasterizationPropertiesKHR{};
	VkPhysicalDeviceMaintenance3Properties Maintenance3Properties{};
	VkPhysicalDeviceMaintenance4Properties Maintenance4Properties{};
	//VkPhysicalDeviceMaintenance5PropertiesKHR Maintenance5PropertiesKHR{};
	//VkPhysicalDeviceMaintenance6PropertiesKHR Maintenance6PropertiesKHR{};
	//VkPhysicalDeviceMapMemoryPlacedPropertiesEXT MapMemoryPlacedPropertiesEXT{};
	VkPhysicalDeviceMemoryDecompressionPropertiesNV MemoryDecompressionPropertiesNV{};
	VkPhysicalDeviceMeshShaderPropertiesEXT MeshShaderPropertiesEXT{};
	VkPhysicalDeviceMeshShaderPropertiesNV MeshShaderPropertiesNV{};
	VkPhysicalDeviceMultiDrawPropertiesEXT MultiDrawPropertiesEXT{};
	VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX MultiviewPerViewAttributesPropertiesNVX{};
	VkPhysicalDeviceMultiviewProperties MultiviewProperties{};
	//VkPhysicalDeviceNestedCommandBufferPropertiesEXT NestedCommandBufferPropertiesEXT{};
	VkPhysicalDeviceOpacityMicromapPropertiesEXT OpacityMicromapPropertiesEXT{};
	VkPhysicalDeviceOpticalFlowPropertiesNV OpticalFlowPropertiesNV{};
	VkPhysicalDevicePCIBusInfoPropertiesEXT PCIBusInfoPropertiesEXT{};
	VkPhysicalDevicePerformanceQueryPropertiesKHR PerformanceQueryPropertiesKHR{};
	VkPhysicalDevicePipelineRobustnessPropertiesEXT PipelineRobustnessPropertiesEXT{};
	VkPhysicalDevicePointClippingProperties PointClippingProperties{};
	//VkPhysicalDevicePortabilitySubsetPropertiesKHR PortabilitySubsetPropertiesKHR{};
	VkPhysicalDeviceProtectedMemoryProperties ProtectedMemoryProperties{};
	VkPhysicalDeviceProvokingVertexPropertiesEXT ProvokingVertexPropertiesEXT{};
	VkPhysicalDevicePushDescriptorPropertiesKHR PushDescriptorPropertiesKHR{};
	VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV RayTracingInvocationReorderPropertiesNV{};
	VkPhysicalDeviceRayTracingPipelinePropertiesKHR RayTracingPipelinePropertiesKHR{};
	VkPhysicalDeviceRayTracingPropertiesNV RayTracingPropertiesNV{};
	//VkPhysicalDeviceRenderPassStripedPropertiesARM RenderPassStripedPropertiesARM{};
	VkPhysicalDeviceRobustness2PropertiesEXT Robustness2PropertiesEXT{};
	VkPhysicalDeviceSampleLocationsPropertiesEXT SampleLocationsPropertiesEXT{};
	VkPhysicalDeviceSamplerFilterMinmaxProperties SamplerFilterMinmaxProperties{};
	//VkPhysicalDeviceSchedulingControlsPropertiesARM SchedulingControlsPropertiesARM{};
	VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM ShaderCoreBuiltinsPropertiesARM{};
	VkPhysicalDeviceShaderCoreProperties2AMD ShaderCoreProperties2AMD{};
	VkPhysicalDeviceShaderCorePropertiesAMD ShaderCorePropertiesAMD{};
	VkPhysicalDeviceShaderCorePropertiesARM ShaderCorePropertiesARM{};
	//VkPhysicalDeviceShaderEnqueuePropertiesAMDX ShaderEnqueuePropertiesAMDX{};
	VkPhysicalDeviceShaderIntegerDotProductProperties ShaderIntegerDotProductProperties{};
	VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT ShaderModuleIdentifierPropertiesEXT{};
	VkPhysicalDeviceShaderObjectPropertiesEXT ShaderObjectPropertiesEXT{};
	VkPhysicalDeviceShaderSMBuiltinsPropertiesNV ShaderSMBuiltinsPropertiesNV{};
	VkPhysicalDeviceShaderTileImagePropertiesEXT ShaderTileImagePropertiesEXT{};
	VkPhysicalDeviceShadingRateImagePropertiesNV ShadingRateImagePropertiesNV{};
	VkPhysicalDeviceSubgroupProperties SubgroupProperties{};
	VkPhysicalDeviceSubgroupSizeControlProperties SubgroupSizeControlProperties{};
	VkPhysicalDeviceSubpassShadingPropertiesHUAWEI SubpassShadingPropertiesHUAWEI{};
	VkPhysicalDeviceTexelBufferAlignmentProperties TexelBufferAlignmentProperties{};
	VkPhysicalDeviceTimelineSemaphoreProperties TimelineSemaphoreProperties{};
	VkPhysicalDeviceTransformFeedbackPropertiesEXT TransformFeedbackPropertiesEXT{};
	VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT VertexAttributeDivisorPropertiesEXT{};
	//VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR VertexAttributeDivisorPropertiesKHR{};
	VkPhysicalDeviceVulkan11Properties Vulkan11Properties{};
	VkPhysicalDeviceVulkan12Properties Vulkan12Properties{};
	VkPhysicalDeviceVulkan13Properties Vulkan13Properties{};

	
	PhysicalDeviceProperties() {
		Init();
	}
	void Init()
	{
		Properties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		Properties2.pNext = &AccelerationStructurePropertiesKHR;
		AccelerationStructurePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
		AccelerationStructurePropertiesKHR.pNext = &BlendOperationAdvancedPropertiesEXT;
		BlendOperationAdvancedPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
		BlendOperationAdvancedPropertiesEXT.pNext = &ClusterCullingShaderPropertiesHUAWEI;
		ClusterCullingShaderPropertiesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_PROPERTIES_HUAWEI;
		
		ClusterCullingShaderPropertiesHUAWEI.pNext = &ConservativeRasterizationPropertiesEXT;
		ConservativeRasterizationPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
		ConservativeRasterizationPropertiesEXT.pNext = &CooperativeMatrixPropertiesNV;
		//VkPhysicalDeviceCooperativeMatrixPropertiesKHR CooperativeMatrixPropertiesKHR;
		CooperativeMatrixPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
		CooperativeMatrixPropertiesNV.pNext = &CopyMemoryIndirectPropertiesNV;

		CopyMemoryIndirectPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_NV;
		CopyMemoryIndirectPropertiesNV.pNext = &CustomBorderColorPropertiesEXT;
		//VkPhysicalDeviceCudaKernelLaunchPropertiesNV CudaKernelLaunchPropertiesNV;
		CustomBorderColorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT;
		CustomBorderColorPropertiesEXT.pNext = &DepthStencilResolveProperties;

		DepthStencilResolveProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
		DepthStencilResolveProperties.pNext = &DescriptorBufferDensityMapPropertiesEXT;

		DescriptorBufferDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT;
		DescriptorBufferDensityMapPropertiesEXT.pNext = &DescriptorBufferPropertiesEXT;

		DescriptorBufferPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;
		DescriptorBufferPropertiesEXT.pNext = &DescriptorIndexingProperties;
		DescriptorIndexingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;
		DescriptorIndexingProperties.pNext = &DeviceGeneratedCommandsPropertiesNV;

		DeviceGeneratedCommandsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV;
		DeviceGeneratedCommandsPropertiesNV.pNext = &DiscardRectanglePropertiesEXT;
		DiscardRectanglePropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
		DiscardRectanglePropertiesEXT.pNext = &DriverProperties;
		//VkPhysicalDeviceDisplacementMicromapPropertiesNV DisplacementMicromapPropertiesNV;
		DriverProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
		DriverProperties.pNext = &DrmPropertiesEXT;

		DrmPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
		DrmPropertiesEXT.pNext = &ExtendedDynamicState3PropertiesEXT;
		ExtendedDynamicState3PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_PROPERTIES_EXT;
		ExtendedDynamicState3PropertiesEXT.pNext = &ExternalMemoryHostPropertiesEXT;

		//VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV ExtendedSparseAddressSpacePropertiesNV;
		//VkPhysicalDeviceExternalFormatResolvePropertiesANDROID ExternalFormatResolvePropertiesANDROID;
		ExternalMemoryHostPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
		ExternalMemoryHostPropertiesEXT.pNext = &FloatControlsProperties;		
		FloatControlsProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES;
		FloatControlsProperties.pNext = &FragmentDensityMap2PropertiesEXT;
		FragmentDensityMap2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT;
		FragmentDensityMap2PropertiesEXT.pNext = &FragmentDensityMapOffsetPropertiesQCOM;
		FragmentDensityMapOffsetPropertiesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM;
		FragmentDensityMapOffsetPropertiesQCOM.pNext = &FragmentDensityMapPropertiesEXT;
		FragmentDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
		FragmentDensityMapPropertiesEXT.pNext = &FragmentShaderBarycentricPropertiesKHR;
		FragmentShaderBarycentricPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_PROPERTIES_KHR;
		FragmentShaderBarycentricPropertiesKHR.pNext = &FragmentShadingRateEnumsPropertiesNV;
		FragmentShadingRateEnumsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;
		FragmentShadingRateEnumsPropertiesNV.pNext = &FragmentShadingRatePropertiesKHR;
		FragmentShadingRatePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
		FragmentShadingRatePropertiesKHR.pNext = &GraphicsPipelineLibraryPropertiesEXT;
		GraphicsPipelineLibraryPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_PROPERTIES_EXT;
		GraphicsPipelineLibraryPropertiesEXT.pNext = &IDProperties;
		////VkPhysicalDeviceHostImageCopyPropertiesEXT HostImageCopyPropertiesEXT;
		IDProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
		IDProperties.pNext = &ImageProcessingPropertiesQCOM;
		//VkPhysicalDeviceImageAlignmentControlPropertiesMESA mageAlignmentControlPropertiesMESA;
		//VkPhysicalDeviceImageProcessing2PropertiesQCOM ImageProcessing2PropertiesQCOM;
		ImageProcessingPropertiesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_PROPERTIES_QCOM;
		ImageProcessingPropertiesQCOM.pNext = &InlineUniformBlockProperties;
		InlineUniformBlockProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES;
		InlineUniformBlockProperties.pNext = &Maintenance3Properties;
		//VkPhysicalDeviceLayeredDriverPropertiesMSFT LayeredDriverPropertiesMSFT;
		//VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT VertexAttributesPropertiesEXT;
		//VkPhysicalDeviceLineRasterizationPropertiesKHR LineRasterizationPropertiesKHR;
		Maintenance3Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
		Maintenance3Properties.pNext = &Maintenance4Properties;
		Maintenance4Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES;
		Maintenance4Properties.pNext = &MemoryDecompressionPropertiesNV;
		//VkPhysicalDeviceMaintenance5PropertiesKHR Maintenance5PropertiesKHR;
		//VkPhysicalDeviceMaintenance6PropertiesKHR Maintenance6PropertiesKHR;
		//VkPhysicalDeviceMapMemoryPlacedPropertiesEXT MapMemoryPlacedPropertiesEXT;
		MemoryDecompressionPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
		MemoryDecompressionPropertiesNV.pNext = &MeshShaderPropertiesEXT;
		MeshShaderPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
		MeshShaderPropertiesEXT.pNext = &MeshShaderPropertiesNV;
		MeshShaderPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
		MeshShaderPropertiesNV.pNext = &MultiDrawPropertiesEXT;
		MultiDrawPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT;
		MultiDrawPropertiesEXT.pNext = &MultiviewPerViewAttributesPropertiesNVX;
		MultiviewPerViewAttributesPropertiesNVX.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
		MultiviewPerViewAttributesPropertiesNVX.pNext = &MultiviewProperties;
		MultiviewProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
		MultiviewProperties.pNext = &OpacityMicromapPropertiesEXT;
		//VkPhysicalDeviceNestedCommandBufferPropertiesEXT NestedCommandBufferPropertiesEXT;
		OpacityMicromapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_PROPERTIES_EXT;
		OpacityMicromapPropertiesEXT.pNext = &OpticalFlowPropertiesNV;
		OpticalFlowPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV;
		OpticalFlowPropertiesNV.pNext = &PCIBusInfoPropertiesEXT;
		PCIBusInfoPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT;
		PCIBusInfoPropertiesEXT.pNext = &PerformanceQueryPropertiesKHR;
		PerformanceQueryPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR;
		PerformanceQueryPropertiesKHR.pNext = &PipelineRobustnessPropertiesEXT;
		PipelineRobustnessPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_PROPERTIES_EXT;
		PipelineRobustnessPropertiesEXT.pNext = &PointClippingProperties;
		PointClippingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
		PointClippingProperties.pNext = &ProtectedMemoryProperties;
		//VkPhysicalDevicePortabilitySubsetPropertiesKHR PortabilitySubsetPropertiesKHR;
		ProtectedMemoryProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
		ProtectedMemoryProperties.pNext = &ProvokingVertexPropertiesEXT;
		ProvokingVertexPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT;
		ProvokingVertexPropertiesEXT.pNext = &PushDescriptorPropertiesKHR;
		PushDescriptorPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
		PushDescriptorPropertiesKHR.pNext = &RayTracingInvocationReorderPropertiesNV;
		RayTracingInvocationReorderPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_PROPERTIES_NV;
		RayTracingInvocationReorderPropertiesNV.pNext = &RayTracingPipelinePropertiesKHR;
		RayTracingPipelinePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
		RayTracingPipelinePropertiesKHR.pNext = &RayTracingPropertiesNV;
		RayTracingPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
		RayTracingPropertiesNV.pNext = &Robustness2PropertiesEXT;
		//VkPhysicalDeviceRenderPassStripedPropertiesARM RenderPassStripedPropertiesARM;
		Robustness2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT;
		Robustness2PropertiesEXT.pNext = &SampleLocationsPropertiesEXT;
		SampleLocationsPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
		SampleLocationsPropertiesEXT.pNext = &SamplerFilterMinmaxProperties;
		SamplerFilterMinmaxProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES;
		SamplerFilterMinmaxProperties.pNext = &ShaderCoreBuiltinsPropertiesARM;
		//VkPhysicalDeviceSchedulingControlsPropertiesARM SchedulingControlsPropertiesARM;
		ShaderCoreBuiltinsPropertiesARM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_PROPERTIES_ARM;
		ShaderCoreBuiltinsPropertiesARM.pNext = &ShaderCoreProperties2AMD;
		ShaderCoreProperties2AMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
		ShaderCoreProperties2AMD.pNext = &ShaderCorePropertiesAMD;
		ShaderCorePropertiesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
		ShaderCorePropertiesAMD.pNext = &ShaderCorePropertiesARM;
		ShaderCorePropertiesARM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_ARM;
		ShaderCorePropertiesARM.pNext = &ShaderIntegerDotProductProperties;
		//VkPhysicalDeviceShaderEnqueuePropertiesAMDX ShaderEnqueuePropertiesAMDX;
		ShaderIntegerDotProductProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES;
		ShaderIntegerDotProductProperties.pNext = &ShaderModuleIdentifierPropertiesEXT;
		ShaderModuleIdentifierPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_PROPERTIES_EXT;
		ShaderModuleIdentifierPropertiesEXT.pNext = &ShaderObjectPropertiesEXT;
		ShaderObjectPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_PROPERTIES_EXT;
		ShaderObjectPropertiesEXT.pNext = &ShaderSMBuiltinsPropertiesNV;
		//VkPhysicalDeviceShaderSMBuiltinsPropertiesNV
		ShaderSMBuiltinsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
		ShaderSMBuiltinsPropertiesNV.pNext = &ShaderTileImagePropertiesEXT;
		ShaderTileImagePropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_PROPERTIES_EXT;
		ShaderTileImagePropertiesEXT.pNext = &ShadingRateImagePropertiesNV;
		ShadingRateImagePropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
		ShadingRateImagePropertiesNV.pNext = &SubgroupProperties;
		SubgroupProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
		SubgroupProperties.pNext = &SubgroupSizeControlProperties;
		SubgroupSizeControlProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES;
		SubgroupSizeControlProperties.pNext = &SubpassShadingPropertiesHUAWEI;
		SubpassShadingPropertiesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_PROPERTIES_HUAWEI;
		SubpassShadingPropertiesHUAWEI.pNext = &TexelBufferAlignmentProperties;
		TexelBufferAlignmentProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES;
		TexelBufferAlignmentProperties.pNext = &TimelineSemaphoreProperties;
		TimelineSemaphoreProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
		TimelineSemaphoreProperties.pNext = &TransformFeedbackPropertiesEXT;
		TransformFeedbackPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
		TransformFeedbackPropertiesEXT.pNext = &VertexAttributeDivisorPropertiesEXT;
		VertexAttributeDivisorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
		VertexAttributeDivisorPropertiesEXT.pNext = &Vulkan11Properties;
		//VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR VertexAttributeDivisorPropertiesKHR;
		Vulkan11Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
		Vulkan11Properties.pNext = &Vulkan12Properties;
		Vulkan12Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
		Vulkan12Properties.pNext = &Vulkan13Properties;
		Vulkan13Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
		Vulkan13Properties.pNext = nullptr;
	}

};

struct QueueFamilyProperties
{
	VkQueueFamilyProperties2 Properties2{};
	VkQueueFamilyCheckpointProperties2NV CheckpointProperties2NV{};
	VkQueueFamilyCheckpointPropertiesNV CheckpointPropertiesNV{};
	VkQueueFamilyGlobalPriorityPropertiesKHR GlobalPriorityPropertiesKHR{};
	VkQueueFamilyQueryResultStatusPropertiesKHR QueryResultStatusPropertiesKHR{};
	VkQueueFamilyVideoPropertiesKHR VideoPropertiesKHR{};
	QueueFamilyProperties() {
		Init();
	}
	void Init() {
		Properties2.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
		Properties2.pNext = &CheckpointProperties2NV;
		CheckpointProperties2NV.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV;
		CheckpointProperties2NV.pNext = &CheckpointPropertiesNV;
		CheckpointPropertiesNV.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV;
		CheckpointPropertiesNV.pNext = &GlobalPriorityPropertiesKHR;
		GlobalPriorityPropertiesKHR.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES_KHR;
		GlobalPriorityPropertiesKHR.pNext = &QueryResultStatusPropertiesKHR;
		QueryResultStatusPropertiesKHR.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_KHR;
		QueryResultStatusPropertiesKHR.pNext = &VideoPropertiesKHR;
		VideoPropertiesKHR.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR;
		VideoPropertiesKHR.pNext = nullptr;

	}
	void* GetFirstPropertiesStructureAddress()const {
		return (void*)&CheckpointProperties2NV;
	}
};



DeviceAndQueueTest::DeviceAndQueueTest()
{
	PrepareContex();
}
DeviceAndQueueTest::~DeviceAndQueueTest()
{
	ClearContex();
}

std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance instance)
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	std::vector<VkPhysicalDevice> devices(count);
	vkEnumeratePhysicalDevices(instance, &count, devices.data());
	return devices;
}
//获取物理设备的比较核心的属性信息 VkPhysicalDeviceProperties没有stype和pnext
std::vector<VkPhysicalDeviceProperties> GetPhysicalDeviceProperties(const std::vector<VkPhysicalDevice>& physicalDevices)
{
	std::vector<VkPhysicalDeviceProperties> properties;
	properties.resize(physicalDevices.size());
	for (uint32_t i = 0; i < properties.size(); i++)
	{
		vkGetPhysicalDeviceProperties(physicalDevices[i], &properties[i]);
	}
	return properties;

}

//获取物理设备的核心的属性以及其他的属性信息测试 VkPhysicalDeviceProperties2有stype和pnext，其中pnext用来传入拓展
//属性的结构体如VkPhysicalDeviceVulkan13Properties来查询vulkan13接口的信息
void GetPhysicalDeviceProperties2Test(const std::vector<VkPhysicalDevice>& physicalDevices) {
	std::vector<VkPhysicalDeviceProperties2> properties2;
	std::vector<VkPhysicalDeviceVulkan13Properties> vulkan13Props;
	vulkan13Props.resize(physicalDevices.size());

	properties2.resize(physicalDevices.size());
	for (uint32_t i = 0; i < properties2.size(); i++)
	{
		VkPhysicalDeviceVulkan13Properties& vulkan13Prop = vulkan13Props[i];
		vulkan13Prop.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
		properties2[i].pNext = &vulkan13Prop;
		vkGetPhysicalDeviceProperties2(physicalDevices[i], &properties2[i]);
	}


	for (uint32_t i = 0; i < properties2.size(); i++)
	{
		auto& prop = properties2[i];
		std::cout << "Device Name: " << prop.properties.deviceName << std::endl;
		std::cout << "Device Type: " << prop.properties.deviceType << std::endl;
		std::cout << "API Version: " << prop.properties.apiVersion << std::endl;
		std::cout << "Driver Version: " << prop.properties.driverVersion << std::endl;
		std::cout << "Vendor ID: " << prop.properties.vendorID << std::endl;
		std::cout << "Device ID: " << prop.properties.deviceID << std::endl;
		std::cout << "Device UUID: " << prop.properties.pipelineCacheUUID << std::endl;
		std::cout << "Device Limits: " << std::endl;
		std::cout << "maxImageDimension1D: " << prop.properties.limits.maxImageDimension1D << std::endl;
		std::cout << "maxImageDimension2D: " << prop.properties.limits.maxImageDimension2D << std::endl;
		std::cout << "maxImageDimension3D: " << prop.properties.limits.maxImageDimension3D << std::endl;
		std::cout << "maxImageDimensionCube: " << prop.properties.limits.maxImageDimensionCube << std::endl;
		std::cout << "maxImageArrayLayers: " << prop.properties.limits.maxImageArrayLayers << std::endl;
		std::cout << "maxTexelBufferElements: " << prop.properties.limits.maxTexelBufferElements << std::endl;
		std::cout << "maxUniformBufferRange: " << prop.properties.limits.maxUniformBufferRange << std::endl;
		std::cout << "maxStorageBufferRange: " << prop.properties.limits.maxStorageBufferRange << std::endl;
		std::cout << "maxPushConstantsSize: " << prop.properties.limits.maxPushConstantsSize << std::endl;
		std::cout << "maxMemoryAllocationCount: " << prop.properties.limits.maxMemoryAllocationCount << std::endl;
		std::cout << "maxSamplerAllocationCount: " << prop.properties.limits.maxSamplerAllocationCount << std::endl;
		std::cout << "bufferImageGranularity: " << prop.properties.limits.bufferImageGranularity << std::endl;
		if (prop.pNext != nullptr)
		{

		}
	}
}


//获取物理设备的核心的属性以及其他的属性信息测试 VkPhysicalDeviceProperties2有stype和pnext，其中pnext用来传入拓展属性结构体指针
std::vector<PhysicalDeviceProperties> GetPhysicalDeviceProperties2(const std::vector<VkPhysicalDevice>& physicalDevices)
{
	std::vector<PhysicalDeviceProperties> propertiesNeedBeFilled;

	propertiesNeedBeFilled.resize(physicalDevices.size());

	for (uint32_t i = 0; i < propertiesNeedBeFilled.size(); i++)
	{

		vkGetPhysicalDeviceProperties2(physicalDevices[i], &propertiesNeedBeFilled[i].Properties2);
	}
	return propertiesNeedBeFilled;
}


//获取物理设备队列的比较核心的属性信息 VkQueueFamilyProperties没有stype和pnext
std::vector<std::vector<VkQueueFamilyProperties>> GetPhysicalDeviceQueueFamilyPeoperties(const std::vector<VkPhysicalDevice>& physicalDevices) {

	std::vector<std::vector<VkQueueFamilyProperties>> physicalDeviceQueueFamilyProperties;
	physicalDeviceQueueFamilyProperties.resize(physicalDevices.size());
	for (uint32_t i = 0; i < physicalDevices.size(); i++)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyCount, nullptr);
		physicalDeviceQueueFamilyProperties[i].resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyCount, physicalDeviceQueueFamilyProperties[i].data());
	}
	return physicalDeviceQueueFamilyProperties;

}

//获取物理设备队列的核心的属性以及其他的属性信息测试 VkPhysicalDeviceProperties2有stype和pnext，其中pnext用来传入拓展属性结构体指针
std::vector<std::vector<QueueFamilyProperties>> GetPhysicalDeviceQueueFamilyPeoperties2(const std::vector<VkPhysicalDevice>& physicalDevices) {

	std::vector<std::vector<QueueFamilyProperties>> physicalDeviceQueueFamilyProperties2;
	physicalDeviceQueueFamilyProperties2.resize(physicalDevices.size());
	for (uint32_t i = 0; i < physicalDevices.size(); i++)
	{

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevices[i], &queueFamilyCount, nullptr);
		physicalDeviceQueueFamilyProperties2[i].resize(queueFamilyCount);
		std::vector<VkQueueFamilyProperties2> tmp;
		tmp.resize(queueFamilyCount);
		for (uint32_t ti = 0; ti < queueFamilyCount; ti++)
		{
			tmp[ti] = physicalDeviceQueueFamilyProperties2[i][ti].Properties2;
		}
		vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevices[i], &queueFamilyCount, tmp.data());
		for (uint32_t ti = 0; ti < queueFamilyCount; ti++)
		{
			physicalDeviceQueueFamilyProperties2[i][ti].Properties2 = tmp[ti];
		}
	}
	return physicalDeviceQueueFamilyProperties2;

}

//队列性能计数器测试
struct QueueFamilyPerformanceCounter
{
	VkPerformanceCounterKHR counter{};
	VkPerformanceCounterDescriptionKHR description{};
	QueueFamilyPerformanceCounter() {

	}
	void Init() {
		counter.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR;
		description.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR;

	}

};

//获取指定物理设备指定队列的所有计数器 // Provided by VK_KHR_performance_query（查询）
//vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR需要VK_KHR_performance_query支持
std::vector<std::vector<QueueFamilyPerformanceCounter>> GetPhysicalDeviceQueueFamilyCounter(const VkInstance instance ,const VkPhysicalDevice physicalDevice,const std::vector<uint32_t>& queueFamilyIndexs) {

	std::vector<std::vector<QueueFamilyPerformanceCounter>> counters;
	counters.resize(queueFamilyIndexs.size());
	auto pvkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
	if (!pvkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR) {
		_ASSERT(0);
	}
	for (uint32_t i = 0; i < queueFamilyIndexs.size(); i++)
	{
		uint32_t numCounter = 0;
		pvkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndexs[i], &numCounter, nullptr, nullptr);
		counters[i].resize(numCounter);
		std::vector<VkPerformanceCounterKHR> tmpCounter;
		tmpCounter.resize(numCounter);
		std::vector<VkPerformanceCounterDescriptionKHR> tmpDescription;
		tmpDescription.resize(numCounter);
		pvkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndexs[i], &numCounter, tmpCounter.data(), tmpDescription.data());
		for (uint32_t ti = 0; ti < numCounter; ti++)
		{
			counters[i][ti].counter = tmpCounter[ti];
			counters[i][ti].description = tmpDescription[ti];
		}

	}
	return counters;

}

//获取设备组属性信息,注意，设备必须是完全一样的才能组成设备组，如果设备组中的设备每个都不一样，
//那么有多少个设备就会有多少个设备组，每个设备组中只有一个设备
//vkEnumeratePhysicalDeviceGroups(vk1.1)等价于vkEnumeratePhysicalDeviceGroupsKHR
std::vector<VkPhysicalDeviceGroupProperties> GetPhysicalDeviceGroupPros(const VkInstance instance) {
	std::vector<VkPhysicalDeviceGroupProperties> physicalDeviceGroupProps;
	uint32_t numPhysicalDeviceGroupProps = 0;
	vkEnumeratePhysicalDeviceGroups(instance, &numPhysicalDeviceGroupProps, nullptr);
	physicalDeviceGroupProps.resize(numPhysicalDeviceGroupProps);
	vkEnumeratePhysicalDeviceGroups(instance, &numPhysicalDeviceGroupProps, physicalDeviceGroupProps.data());
	return physicalDeviceGroupProps;

	
}

//获取物理设备的核心扩展属性
std::vector<VkExtensionProperties> GetPhysicalDeviceExtension(const VkPhysicalDevice physicalDevice)
{

	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions.data());
	return extensions;
}

//获取物理设备的核心层属性,在新的vulkanAPI中,层的概念已经被废弃，但是为了兼容旧的代码，还是保留了层的概念
//本次测试用例中，层的概念不会被使用
std::vector<VkLayerProperties> GetPhysicalDeviceLayer(const VkPhysicalDevice physicalDevice)
{
	uint32_t layerCount = 0;
	vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, nullptr);
	std::vector<VkLayerProperties> layers(layerCount);
	vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, layers.data());
	return layers;
}

extern bool CheckExtensionSurport(const char* extensionName, const  std::vector<VkExtensionProperties>& extensions);

//获取核心特性支持的扩展属性
VkPhysicalDeviceFeatures GetPhysicalDeviceFeature(const VkPhysicalDevice physicalDevice) {

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(physicalDevice, &features);
	return features;

}

//获取核心特性支持的扩展属性以及额外的扩展属性
VkPhysicalDeviceFeatures2 GetPhysicalDeviceFeature2(const VkPhysicalDevice physicalDevice) {
	VkPhysicalDeviceFeatures2 features2;
	vkGetPhysicalDeviceFeatures2(physicalDevice, &features2);
	return features2;
}

//
//注: 剩下的一些关于物理设备的属性获取函数，如获取物理设备的内存属性，物理设备的格式属性等等，这里就不再一一列举了
//会在后续的测试用例中逐一补充


void DeviceAndQueueTest::run()
{


	//TODO: 编写测试用例代码
	auto physicalDevices = GetPhysicalDevices(instance);
	auto properties = GetPhysicalDeviceProperties(physicalDevices);

	for (uint32_t i = 0; i < properties.size(); i++)
	{
		auto& prop = properties[i];
		std::cout << "Device Name: " << prop.deviceName << std::endl;
		std::cout << "Device Type: " << prop.deviceType << std::endl;
		std::cout << "API Version: " << prop.apiVersion << std::endl;
		std::cout << "Driver Version: " << prop.driverVersion << std::endl;
		std::cout << "Vendor ID: " << prop.vendorID << std::endl;
		std::cout << "Device ID: " << prop.deviceID << std::endl;
		std::cout << "Device UUID: " << prop.pipelineCacheUUID << std::endl;
		std::cout << "Device Limits: " << std::endl;
		std::cout << "maxImageDimension1D: " << prop.limits.maxImageDimension1D << std::endl;
		std::cout << "maxImageDimension2D: " << prop.limits.maxImageDimension2D << std::endl;
		std::cout << "maxImageDimension3D: " << prop.limits.maxImageDimension3D << std::endl;
		std::cout << "maxImageDimensionCube: " << prop.limits.maxImageDimensionCube << std::endl;
		std::cout << "maxImageArrayLayers: " << prop.limits.maxImageArrayLayers << std::endl;
		std::cout << "maxTexelBufferElements: " << prop.limits.maxTexelBufferElements << std::endl;
		std::cout << "maxUniformBufferRange: " << prop.limits.maxUniformBufferRange << std::endl;
		std::cout << "maxStorageBufferRange: " << prop.limits.maxStorageBufferRange << std::endl;
		std::cout << "maxPushConstantsSize: " << prop.limits.maxPushConstantsSize << std::endl;
		std::cout << "maxMemoryAllocationCount: " << prop.limits.maxMemoryAllocationCount << std::endl;
		std::cout << "maxSamplerAllocationCount: " << prop.limits.maxSamplerAllocationCount << std::endl;
		std::cout << "bufferImageGranularity: " << prop.limits.bufferImageGranularity << std::endl;
		std::cout << "sparseAddressSpaceSize: " << prop.limits.sparseAddressSpaceSize << std::endl;
	}


	auto physicalDeviceProperties2 = GetPhysicalDeviceProperties2(physicalDevices);

	auto physicalDeviceQueueFamilyProperties = GetPhysicalDeviceQueueFamilyPeoperties(physicalDevices);
	auto physicalDeviceQueueFamilyProperties2 = GetPhysicalDeviceQueueFamilyPeoperties2(physicalDevices);

	std::vector<std::vector<std::vector<QueueFamilyPerformanceCounter>>> counters;
	counters.resize(physicalDevices.size());


	for (uint32_t i = 0; i < physicalDevices.size(); i++)
	{
		std::vector<uint32_t> tmpQueueFamilyIndex;

		for (uint32_t j = 0; j < physicalDeviceQueueFamilyProperties[i].size(); j++)
		{
			physicalDeviceQueueFamilyProperties[i][j].queueFlags;
			tmpQueueFamilyIndex.push_back(j);
		}
		//counters[i] = GetPhysicalDeviceQueueFamilyCounter(instance,physicalDevices[i], tmpQueueFamilyIndex);
	}

	auto physicalDeviceGroupProps = GetPhysicalDeviceGroupPros(instance);

	physicalDevice = physicalDevices[0];
	VkDeviceCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
	queueCreateInfos.resize(physicalDeviceQueueFamilyProperties[0].size());
	std::vector<const float*> tmpNewPointer;
	for (uint32_t i = 0; i < queueCreateInfos.size(); i++)
	{
		auto& queueCreateInfo = queueCreateInfos[i];
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = i;
		queueCreateInfo.flags = 0;//这里可以设置是否是protected的队列
		queueCreateInfo.queueCount = physicalDeviceQueueFamilyProperties[0][i].queueCount;
		queueCreateInfo.pQueuePriorities = new float[queueCreateInfo.queueCount];//队列的优先级似乎有两级,一级为
		//系统级别的优先级，另一级为队列级别的优先级(同一系统优先级下的优先级)
		tmpNewPointer.push_back(queueCreateInfo.pQueuePriorities);
		queueCreateInfo.pNext = nullptr;//见vulkan specification p193
	}

	auto extensions = GetPhysicalDeviceExtension(physicalDevice);

	bool swapChainEXTSurport = CheckExtensionSurport(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extensions);
	std::vector<const char*> wantExtensions;
	if (swapChainEXTSurport)
	{
		wantExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}
	//可以设置负数viewport的高度拓展
	bool negativeViewportHeightSurport = CheckExtensionSurport(VK_KHR_MAINTENANCE1_EXTENSION_NAME, extensions);
	if (negativeViewportHeightSurport) {
		wantExtensions.push_back(VK_KHR_MAINTENANCE1_EXTENSION_NAME);
	}
	
	//features
	auto features = GetPhysicalDeviceFeature(physicalDevice);
	info.pEnabledFeatures = &features;//如果需要用除了核心特性之外的特性，需要使用VkPhysicalDeviceFeatures2,
	//这里需要设置为nullptr,并且在VkDeviceCreateInfo.pnext中要包含VkPhysicalDeviceFeatures2的结构体

	info.pNext = nullptr;//具体的细节较多详细的见vulkan specification p193 , 简要理解可以认为如果有些特性或拓展(在pExtensionNams中需有)需要额外的结构体，那么这个结构体就要放在pNext中
	
	//extensions
	info.enabledExtensionCount = wantExtensions.size();
	info.ppEnabledExtensionNames = wantExtensions.data();

	//layers
	//由于之前有提到在新的vulkan接口版本中,device已经没有layer概念了,所以这里测试直接省略
	info.enabledLayerCount = 0;
	info.ppEnabledLayerNames = nullptr;




	//常规方式创建一个device
	auto res = vkCreateDevice(physicalDevice, &info, nullptr, &device);
	if (res != VK_SUCCESS)
	{
		_ASSERT(0);
	}

	vkDestroyDevice(device, nullptr);

	//通过设备组的方式创建一个device,表示创建基于该物理设备创建的device属于该物理设备组
	VkDeviceGroupDeviceCreateInfo groupInfo{};
	groupInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
	groupInfo.pNext = nullptr;
	groupInfo.physicalDeviceCount = physicalDeviceGroupProps[0].physicalDeviceCount;
	groupInfo.pPhysicalDevices = physicalDeviceGroupProps[0].physicalDevices;
	info.pNext = &groupInfo;
	res = vkCreateDevice(physicalDevice, &info, nullptr, &device);
	if (res != VK_SUCCESS)
	{
		_ASSERT(0);
	}

	VkQueue queue{ VK_NULL_HANDLE };
	vkGetDeviceQueue(device, 0, 0, &queue);
	//如果队列创建的时候设置了flags,即VkDeviceQueueCreateInfo.flags不为0,那么这里需要使用vkGetDeviceQueue2
	//VkDeviceQueueInfo2 queueInfo2{};
	//vkGetDeviceQueue2(device, &queueInfo2,&queue);

	vkDestroyDevice(device, nullptr);
}


NS_TEST_END
