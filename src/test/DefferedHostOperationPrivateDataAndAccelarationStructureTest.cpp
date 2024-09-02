#include "DefferedHostOperationPrivateDataAndAccelarationStructureTest.h"
NS_TEST_BEGIN
DefferedHostOperationPrivateDataAndAccelarationStructureTest::DefferedHostOperationPrivateDataAndAccelarationStructureTest()
{
}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::run()
{
}

DefferedHostOperationPrivateDataAndAccelarationStructureTest::~DefferedHostOperationPrivateDataAndAccelarationStructureTest()
{
}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::DefferedHostOperationTest()
{
	/*
	deferred operations 允许应用和驱动使用应用管理的线程池去管理和同步耗时昂贵的host端的命令， VK_KHR_deferred_host_operations拓展定义了一些支持这些host端命令的基本机制，只有依赖这个拓展的host端命令才能延迟执行
	
	*/


	//Requesting Deferral   如何请求defer操作以及需要遵循的一些规则的概述 参见p3196

	//Deferred Host Operations API  参见p3197
	{

		VkDeferredOperationKHR/*该结构体体管理defered command的执行状态*/  deferredOperationKHR{};

		//创建一个追踪defered command的VkDeferredOperationKHR对象
		vkCreateDeferredOperationKHR(device, nullptr, &deferredOperationKHR);

		//给一个defered command安排一个线程，该接口在线程中调用
		VkResult deferredOperationJoinResult =  vkDeferredOperationJoinKHR(device, deferredOperationKHR);
		deferredOperationJoinResult;
		/*
		VK_SUCCESS:  指明defered 操作已经完成，应用可以调用vkGetDeferredOperationResultKHR获取其状态
		VK_THREAD_DONE_KHR:  指明defered 操作还未完成但即将完成，已经没有别的工作可以安排给线程了，后续继续调用vkDeferredOperationJoinKHR是不必要的且会影响性能
		VK_THREAD_IDLE_KHR:  指明defered 操作还未完成,但是在调用该函数的时候没有别的工作可以安排给线程，这种情况说明defered 操作的执行遇到了一个参数的平行调度的减少，后续继续调用vkDeferredOperationJoinKHR是可以的		
		*/

		//当defered command完成，销毁其VkDeferredOperationKHR对象
		vkDestroyDeferredOperationKHR(device, deferredOperationKHR, nullptr);
		/*
		vkDestroyDeferredOperationKHR有效用法:
		1.如果创建时提供了VkAllocationCallbacks，则这里必须提供与之兼容的callbacks
		2.如果创建时没有提供VkAllocationCallbacks，则这里pAllocator必须传入NULL
		3.operation必须已经完成
		*/

		//查询还可以有多少个线程通过vkDeferredOperationJoinKHR来等待defered command的完成  ,如果返回pow(2,32) -1 则表示不能估计该需要多少个线程，建议这个接口在开始的时候调用一次
		uint32_t numThreadNeeded = vkGetDeferredOperationMaxConcurrencyKHR(device, deferredOperationKHR);


		//获取defered command的执行的结果或者说执行状态
		VkResult completedResult = vkGetDeferredOperationResultKHR(device, deferredOperationKHR);

	}


}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::PrivateDataTest()
{
	/*
	private data 拓展提供了一种方式可以让用户自己定义的数据关联到vulkan的对象中，这种关联是通过在私有数据槽中存储用户定义数据的64位无符号整数来完成的。私有数据槽表示设备的每个子对象的一个数据项的存储分配
	
	device可以在创建时保留该数据槽，通过在 VkDeviceCreateInfo.pNext中链接所需数量的 VkDevicePrivateDataCreateInfo
	*/

	VkPrivateDataSlot privateDataSlot{};//等价于VkPrivateDataSlotEXT

	//创建一个私有数据槽,  等同与vkCreatePrivateDataSlotEXT
	VkPrivateDataSlotCreateInfo privateDataSlotCreateInfo{};//等价于VkPrivateDataSlotCreateInfoEXT
	privateDataSlotCreateInfo.sType = VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO;
	privateDataSlotCreateInfo.pNext = nullptr;
	privateDataSlotCreateInfo.flags = 0;//保留未来使用

	vkCreatePrivateDataSlot(device, &privateDataSlotCreateInfo, nullptr, &privateDataSlot);// privateData 特性必须开启


	//存储用户定义的数据到一个关联到vulkan对象的私有数据槽中,  等同于vkSetPrivateDataEXT
	vkSetPrivateData(device, VK_OBJECT_TYPE_BUFFER/*objectType，指明关联的vulkan对象的类型*/, (uint64_t)VkBuffer {/*假设这是一个有效的VkBuffer*/ }/* objectHandle，为关联的对象的句柄,必须为device或者从device中创建对象的对应objectType的句柄*/,
		privateDataSlot/* privateDataSlot，VkPrivateDataSlot句柄指明private data存储的位置*/, 1234567890/*data，用户定义的关联到vulkan的数据， 存储到privateDataSlot中*/);

	//从一个关联到vulkan对象的私有数据槽中获取用户定义的数据,  等同于vkGetPrivateDataEXT
	uint64_t privateData = 0;
	vkGetPrivateData(device, VK_OBJECT_TYPE_BUFFER/*objectType，指明关联的vulkan对象的类型*/, (uint64_t)VkBuffer {/*假设这是一个有效的VkBuffer*/ }/* objectHandle，为关联的对象的句柄,必须为device或者从device中创建对象的对应objectType的句柄*/,
		privateDataSlot/* privateDataSlot，VkPrivateDataSlot句柄指明private data存储的位置*/, & privateData/*pData，返回关联到vulkan的存储到privateDataSlot中用户定义的数据，如果之前没有设置则返回0 */);



	//销毁私有数据槽   ，等同于vkDestroyPrivateDataSlotEXT
	vkDestroyPrivateDataSlot(device, privateDataSlot, nullptr);
	/*
	vkDestroyPrivateDataSlot有效用法:
	1.如果创建时提供了VkAllocationCallbacks，则这里必须提供与之兼容的callbacks
	2.如果创建时没有提供VkAllocationCallbacks，则这里pAllocator必须传入NULL
	
	*/




}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::AccelerationStructureTest()
{
	//Acceleration Structures 参见p3210
	{
		/*
		Acceleration Structures加速结构是实现用来高效管理用于ray tracing query遍历场景中几何体的数据。由应用来管理，包含分配，销毁，构建执行和更新，同步在ray tracing query中使用的资源。

		Acceleration Structures分为两种类型：top level acceleration structures 以及 bottom level acceleration structures
		

		*/

		//Geometry  所指为三角形或者是轴向的包围盒

		//Top Level Acceleration Structures   含有对 bottom level acceleration structure的引用，参加p3211

		//Bottom Level Acceleration Structures  为一组geometries的数组

		//Acceleration Structure Update Rules 参见3211
		{
			/*
			Acceleration Structure的产生通过两种方式进行，一种是通过构建操作，一种是通过更新操作

			更新操作有一些限制，在创建加速结构是flags中是否含有VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT，VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT或者VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISPLACEMENT_MICROMAP_UPDATE_NV 有不同的情况，参见 p3211
			*/
		}


		//Inactive Primitives and Instances  参见3212
		{
			/*
			Acceleration structures 允许使用特殊的输入来触发 inactive primitives 或者 instances.
			
			如果一个图元primitive中任何一个顶点的x值为NaN,则说明该图元是inactive的，在构建加速结构时，inactive primitives会被忽略，在ray tracing query中不会被考虑。

			如果一个instance的acceleration structure引用为0，则说明该instance是inactive的，在构建加速结构时，inactive instances会被忽略，在ray tracing query中不会被考虑。
			
			如果最小的x坐标值为NaN，则说明该AABB包围盒是inactive的，在构建加速结构时，inactive AABB包围盒会被忽略，在ray tracing query中不会被考虑。
			
			inactive的primitives和instances不会 InstanceId 以及 PrimitiveId的自动计算
			*/

		}


		//Building Acceleration Structures  参见3213
		{
			VkAccelerationStructureNV srcAccelerationStructureNV{};
			VkAccelerationStructureNV dstAccelerationStructureNV{};
			VkAccelerationStructureKHR srcAccelerationStructureKHR{};
			VkAccelerationStructureKHR dstAccelerationStructureKHR{};
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

			//构架加速结构
			VkAccelerationStructureInfoNV accelerationStructureInfoNV{};
			accelerationStructureInfoNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
			accelerationStructureInfoNV.pNext = nullptr;
			accelerationStructureInfoNV.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV;
			accelerationStructureInfoNV.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV;
			accelerationStructureInfoNV.instanceCount = 1;
			accelerationStructureInfoNV.geometryCount = 1;
			VkGeometryNV geometryNV{};
			{
				geometryNV.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
				geometryNV.pNext = nullptr;
				geometryNV.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_NV;
				geometryNV.flags = VK_GEOMETRY_OPAQUE_BIT_NV;
				VkGeometryDataNV geometryDataNV{};
				{
					VkGeometryTrianglesNV trianglesNV{};
					{
						trianglesNV.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
						trianglesNV.pNext = nullptr;
						trianglesNV.vertexData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
						trianglesNV.vertexOffset = 0;
						trianglesNV.vertexStride = 12;
						trianglesNV.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
						trianglesNV.vertexCount = 3;
						trianglesNV.indexData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
						trianglesNV.indexOffset = 0;
						trianglesNV.indexType = VK_INDEX_TYPE_UINT16;
						trianglesNV.indexCount = 3;
						trianglesNV.transformData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
						trianglesNV.transformOffset = 0;
					}
					geometryDataNV.triangles = trianglesNV;
					VkGeometryAABBNV aabbs{};
					{
						aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
						aabbs.pNext = nullptr;
						aabbs.aabbData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
						aabbs.numAABBs = 1;
						aabbs.offset = 1;
						aabbs.stride = 24;
					}
					geometryDataNV.aabbs = aabbs;
				}
				geometryNV.geometry = geometryDataNV;
			}
			accelerationStructureInfoNV.pGeometries = &geometryNV;

			vkCmdBuildAccelerationStructureNV(commandBuffer, &accelerationStructureInfoNV,
				VkBuffer{/*假设这是一个有效的VkBuffer*/ }/* instanceData，包含一组定义加速结构的VkAccelerationStructureInstanceKHR，如果为bottom level acceleration structures则必须为NULL */, 0/*instanceOffset,为 instanceData中参数的起始字节偏移*/,
				VK_TRUE/*update,指定是否使用src中的数据更新dst中 acceleration structure的数据.*/, dstAccelerationStructureNV/*dst, 指明要构建的acceleration structure*/, srcAccelerationStructureNV/* src，为已经存在的用于更新dst的acceleration structure*/, 
				VkBuffer{/*假设这是一个有效的VkBuffer*/ }/*scratch，为用作创建acceleration structure的 scratch memory的VkBuffer .*/, 0/*scratchOffset,为 scratch中的起始字节偏移量*/);//对src，dst 以及scratch的必须以VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage进行同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR 或者 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR进行访问
			/*
			vkCmdBuildAccelerationStructureNV有效用法:
			1.geometryCount 必须小于等于VkPhysicalDeviceRayTracingPropertiesNV::maxGeometryCount
			2.*dst 必须以兼容的VkAccelerationStructureInfoNV创建，即VkAccelerationStructureInfoNV::type和VkAccelerationStructureInfoNV::flags相同，dst的 VkAccelerationStructureInfoNV::instanceCount以及VkAccelerationStructureInfoNV::geometryCount大于等于构建大小，且dst的VkAccelerationStructureInfoNV::pGeometries 的每个元素的构建大小必须要大于等于vertices, indices, 以及 AABBs的数量。
			3.如果update 为VK_TRUE,则src 不能为VK_NULL_HANDLE，且必须在先前以VkAccelerationStructureInfoNV::flags设置有VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV 创建
			4.如果update 为VK_FALSE，则（1）调用vkGetAccelerationStructureMemoryRequirementsNV传入VkAccelerationStructureMemoryRequirementsInfoNV::accelerationStructure为dst以及VkAccelerationStructureMemoryRequirementsInfoNV::type设置为VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV的参数返回的VkMemoryRequirements中的size 必须小于等于scratch VkBuffer的大小减去scratchOffset
									   （2）调用vkGetAccelerationStructureMemoryRequirementsNV传入VkAccelerationStructureMemoryRequirementsInfoNV::accelerationStructure为dst以及VkAccelerationStructureMemoryRequirementsInfoNV::type设置为VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV的参数返回的VkMemoryRequirements中的size 必须小于等于scratch VkBuffer的大小减去scratchOffset
			5.scratch 必须以VK_BUFFER_USAGE_RAY_TRACING_BIT_NV 创建
			6.如果instanceData 不为VK_NULL_HANDLE，instanceData必须以VK_BUFFER_USAGE_RAY_TRACING_BIT_NV 创建
			7.instanceData中包含的每个VkAccelerationStructureInstanceKHR::accelerationStructureReference的值必须包含了从vkGetAccelerationStructureHandleNV获取的值一个有效的设备地址
			8.如果update 为VK_TRUE，则（1）先前是active的object 不能变为inactive的，见Inactive Primitives and Instances p3212
									  （2）先前是inactive的object 不能变为active的，见Inactive Primitives and Instances p3212
			9.如果update 为VK_FALSE，则src以及dst对象必须同一个对象或者不含有任何memory aliasing
			10.dst 必须通过vkBindAccelerationStructureMemoryNV已经绑定到完整的连续的单独的VkDeviceMemory对象上了
			
			*/



			//构建acceleration structures KHR
			VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{};//其他信息见p3235
			accelerationStructureBuildGeometryInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
			accelerationStructureBuildGeometryInfoKHR.pNext = nullptr;
			accelerationStructureBuildGeometryInfoKHR.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR;//VkBuildAccelerationStructureFlagBitsKHR 组合值位掩码指明额外的参数
			accelerationStructureBuildGeometryInfoKHR.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;//为VkAccelerationStructureTypeKHR 值指明加速结构构建的类型
			accelerationStructureBuildGeometryInfoKHR.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;// VkBuildAccelerationStructureModeKHR 值指明操作的类型
			/*
			VkBuildAccelerationStructureModeKHR:
			VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR:  指明将使用指定的几何体构建dstAccelerationStructure
			VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR:  指明将使用srcAccelerationStructure中的数据构建dstAccelerationStructure，然后更新指定的几何体
			*/
			accelerationStructureBuildGeometryInfoKHR.srcAccelerationStructure = srcAccelerationStructureKHR;//为当mode 为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR的时候用来更新dstAccelerationStructure 的一个现存的 acceleration structure
			accelerationStructureBuildGeometryInfoKHR.dstAccelerationStructure = dstAccelerationStructureKHR;//为要更新的acceleration structure
			accelerationStructureBuildGeometryInfoKHR.geometryCount = 1;//指明要构建到dstAccelerationStructure 中的几何体数量
			VkAccelerationStructureGeometryKHR geometryKHR{};
			{
				geometryKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;;
				geometryKHR.pNext = nullptr;
				geometryKHR.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;//VkGeometryFlagBitsKHR 组合值位掩码指明geometry如何构建的额外信息
				geometryKHR.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;//描述了该加速结构引用的类型
				VkAccelerationStructureGeometryDataKHR geometryDataKHR{};
				{
					VkAccelerationStructureGeometryTrianglesDataKHR trianglesKHR{};
					{
						//
						struct AccelerationStructureGeometryTrianglesDataKHREXT{
							VkAccelerationStructureGeometryMotionTrianglesDataNV accelerationStructureGeometryMotionTrianglesDataNV{};
							VkAccelerationStructureTrianglesDisplacementMicromapNV accelerationStructureTrianglesDisplacementMicromapNV{};
							VkAccelerationStructureTrianglesOpacityMicromapEXT accelerationStructureTrianglesOpacityMicromapEXT{};
							AccelerationStructureGeometryTrianglesDataKHREXT() {
								Init();
							}
							void Init() {
								accelerationStructureGeometryMotionTrianglesDataNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV;
								accelerationStructureGeometryMotionTrianglesDataNV.pNext = nullptr;
								accelerationStructureTrianglesDisplacementMicromapNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
								accelerationStructureTrianglesDisplacementMicromapNV.pNext = nullptr;
								accelerationStructureTrianglesOpacityMicromapEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
								accelerationStructureTrianglesOpacityMicromapEXT.pNext = nullptr;
							}
						
						};




						trianglesKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
						AccelerationStructureGeometryTrianglesDataKHREXT accelerationStructureGeometryTrianglesDataKHREXT{};
						//VkAccelerationStructureGeometryTrianglesDataKHR.pNext
						{
							//VkAccelerationStructureGeometryMotionTrianglesDataNV，  包含该结构体指明再time 1.0时的几何体位置，VkAccelerationStructureGeometryTrianglesDataKHR指明为time 0.0的位置，中间的time通过线性插值进行
							VkAccelerationStructureGeometryMotionTrianglesDataNV& accelerationStructureGeometryMotionTrianglesDataNV = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureGeometryMotionTrianglesDataNV;
							accelerationStructureGeometryMotionTrianglesDataNV.vertexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含该geometry再time 1.0时的顶点数据的device 或者host端的地址


							/*VkAccelerationStructureTrianglesOpacityMicromapEXT，  包含该结构体指明该geometry引用micromap
							
							对几何体中的每个三角形，将使用indexBuffer, indexType 以及 indexStride来构建，如果其中一个索引值由一个  VkOpacityMicromapSpecialIndexEXT的无符号转换得到，则该三角形的行为参考Ray Opacity Micromap.p3333 ,否则将使用micromap中用索引值加上 baseTriangle的 opacity micromap information
							
							VkOpacityMicromapSpecialIndexEXT:
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_TRANSPARENT_EXT:  指明整个三角形完全透明
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_OPAQUE_EXT:  指明整个三角形完全不透明
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_TRANSPARENT_EXT:  指明整个三角形的透明度未知
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_OPAQUE_EXT:  指明整个三角形的不透明度未知
							*/
							VkAccelerationStructureTrianglesOpacityMicromapEXT& accelerationStructureTrianglesOpacityMicromapEXT = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureTrianglesOpacityMicromapEXT;
							accelerationStructureTrianglesOpacityMicromapEXT.baseTriangle = 0;//为添加到非负三角形索引上的一个值
							accelerationStructureTrianglesOpacityMicromapEXT.indexBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含triangle 的索引数据的device 或者host端的地址
							accelerationStructureTrianglesOpacityMicromapEXT.indexStride = 32;//为索引数据中两个索引之间的直接步长
							accelerationStructureTrianglesOpacityMicromapEXT.indexType = VK_INDEX_TYPE_UINT32;//为索引micromap 的三角形顶点索引类型
							accelerationStructureTrianglesOpacityMicromapEXT.micromap = VkMicromapEXT{ /*假设这是一个有效的VkMicromapEXT*/ };//为包含在该geometry内的micromap对象的句柄
							accelerationStructureTrianglesOpacityMicromapEXT.usageCountsCount = 1;//指明usage count结构体的数量，用来定义 micromap的大小
							VkMicromapUsageEXT usageCount{};
							{
								usageCount.count = 1;
								usageCount.format = VK_FORMAT_R8_UNORM;
								usageCount.subdivisionLevel = 0;
							}
							accelerationStructureTrianglesOpacityMicromapEXT.pUsageCounts = &usageCount;//一组VkMicromapUsageEXT 数组指针
							accelerationStructureTrianglesOpacityMicromapEXT.ppUsageCounts = VK_NULL_HANDLE;//一个指向VkMicromapUsageEXT 数组指针的数组指针
							/*
							VkAccelerationStructureTrianglesOpacityMicromapEXT有效用法:
							1.pUsageCounts 和ppUsageCounts中只有一个有效，另外一个必须为VK_NULL_HANDLE
							*/


							/*VkAccelerationStructureTrianglesDisplacementMicromapNV，  包含该结构体指明该geometry引用micromap

							对几何体中的每个三角形，将使用indexBuffer, indexType 以及 indexStride来构建，使用micromap中用索引值加上 baseTriangle的 displacement micromap information
							*/
							VkAccelerationStructureTrianglesDisplacementMicromapNV& accelerationStructureTrianglesDisplacementMicromapNV = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureTrianglesDisplacementMicromapNV;
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleFormat = VK_FORMAT_R32G32B32_SFLOAT;//指明displacement  micromap的 bias 和 scale 的格式
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorFormat = VK_FORMAT_R32G32B32_SFLOAT;//指明displacement  micromap的 displacement vector 的格式
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含displacement  micromap的 bias 和 scale 的device 或者host端的地址
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleStride = 4;//为bias 和 scale 之间的字节步长
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含displacement  micromap的 displacement vector 的device 或者host端的地址
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorStride = 4;//为两个 displacement vector 值之间的字节步长
							accelerationStructureTrianglesDisplacementMicromapNV.displacedMicromapPrimitiveFlags = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含primitive flags 的device 或者host端的地址
							accelerationStructureTrianglesDisplacementMicromapNV.displacedMicromapPrimitiveFlagsStride = 4;//为两个 primitive flags 值之间的字节步长
							accelerationStructureTrianglesDisplacementMicromapNV.indexType = VK_INDEX_TYPE_UINT32;//为索引micromap 的三角形顶点索引类型
							accelerationStructureTrianglesDisplacementMicromapNV.indexBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含triangle 的索引数据的device 或者host端的地址
							accelerationStructureTrianglesDisplacementMicromapNV.indexStride = 32;//为索引数据中两个索引之间的直接步长
							accelerationStructureTrianglesDisplacementMicromapNV.baseTriangle = 0;//为添加到非负三角形索引上的一个值
							accelerationStructureTrianglesDisplacementMicromapNV.usageCountsCount = 1;//值明usage count结构体的数量，用来定义 micromap的大小
							accelerationStructureTrianglesDisplacementMicromapNV.pUsageCounts = &usageCount;//一组VkMicromapUsageEXT 数组指针
							accelerationStructureTrianglesDisplacementMicromapNV.ppUsageCounts = VK_NULL_HANDLE;//一个指向VkMicromapUsageEXT 数组指针的数组指针
							accelerationStructureTrianglesDisplacementMicromapNV.micromap = VkMicromapEXT{ /*假设这是一个有效的VkMicromapEXT*/ };//为包含在该geometry内的micromap对象的句柄
							/*
							VkAccelerationStructureTrianglesDisplacementMicromapNV有效用法:
							1.displacementBiasAndScaleFormat 以及 displacementVectorFormat不能为VK_FORMAT_UNDEFINED
							2.pUsageCounts 和ppUsageCounts中只有一个有效，另外一个必须为VK_NULL_HANDLE
							*/
						}
						trianglesKHR.pNext = &accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureGeometryMotionTrianglesDataNV;
						trianglesKHR.vertexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host 端const地址*/  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含顶点数据的device 或者host端的地址
						trianglesKHR.vertexStride = 12;//为每个顶点间的字节步长大小
						trianglesKHR.maxVertex = 3;//为vertexData 中的顶点数量减去1
						trianglesKHR.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;//为顶点元素的数据VkFormat格式
						trianglesKHR.indexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含索引数据的device 或者host端的地址
						trianglesKHR.indexType = VK_INDEX_TYPE_UINT16;//为索引元素的数据类型 VkIndexType
						//VkTransformMatrixKHR   等价于VkTransformMatrixNV
						{
							VkTransformMatrixKHR  transformMatrixKHR{};
							transformMatrixKHR.matrix;//为3 × 4 行优先的仿射矩阵，前3列必须定义一个可逆的矩阵
							for (uint32_t i = 0; i < 3; i++)
							{
								for (uint32_t j = 0; j < 4; j++)
								{
									transformMatrixKHR.matrix[i][j] = 0;
								}
							}
							
						}
						trianglesKHR.transformData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含可选的VkTransformMatrixKHR 数据的device 或者host端的地址，描述从geometry的顶点所在的空间到加速结构定义所在的空间的变换
						/*
						VkAccelerationStructureGeometryTrianglesDataKHR有效用法:
						1.vertexStride 必须是vertexFormat 的最小分量的字节步长的整数倍
						2.vertexStride 必须小于等于pow(2,32) -1
						3.vertexFormat的format features 必须包含VK_FORMAT_FEATURE_ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR
						4.indexType 必须是 VK_INDEX_TYPE_UINT16, VK_INDEX_TYPE_UINT32 或者 VK_INDEX_TYPE_NONE_KHR
						*/
					}
					geometryDataKHR.triangles = trianglesKHR;// VkAccelerationStructureGeometryTrianglesDataKHR 值 
					VkAccelerationStructureGeometryAabbsDataKHR aabbsKHR{};
					{
						aabbsKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
						aabbsKHR.pNext = nullptr;
						// VkAabbPositionsKHR  等同于VkAabbPositionsNV
						{
							VkAabbPositionsKHR aabbPositionsKHR{};
							aabbPositionsKHR.minX = 0;//为包围盒一个对角的x坐标
							aabbPositionsKHR.minY = 0;//为包围盒一个对角的y坐标
							aabbPositionsKHR.minZ = 0;//为包围盒一个对角的z坐标
							aabbPositionsKHR.maxX = 1;//为包围盒另一个对角的x坐标,必须大于minX
							aabbPositionsKHR.maxY = 1;//为包围盒另一个对角的y坐标,必须大于minY
							aabbPositionsKHR.maxZ = 1;//为包围盒另一个对角的z坐标,必须大于minZ


						}
						aabbsKHR.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含geometry中每个轴向边界盒位置数据 VkAabbPositionsKHR 的device 或者host端的地址
						aabbsKHR.stride = 64;//为data中两个元素之间的字节步长，必须为8的倍数，且必须小于等于pow(2,32)-1
					}
					geometryDataKHR.aabbs = aabbsKHR;// VkAccelerationStructureGeometryAabbsDataKHR 值 
					VkAccelerationStructureGeometryInstancesDataKHR instanceDataKHR{};
					{
						instanceDataKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
						instanceDataKHR.pNext = nullptr;
						{
							/*
							Acceleration structure instances可以构建为一个top-level acceleration structures.每个instance是top-level acceleration structures中分离的组分，包含一个 bottom-level acceleration structure的在变换位置处的所有geometry，多个instance可以指向同一个bottom-level acceleration structure
							*/

							VkAccelerationStructureInstanceKHR accelerationStructureInstanceKHR{}; //等同与VkAccelerationStructureInstanceNV
							accelerationStructureInstanceKHR.accelerationStructureReference = 0;//为vkGetAccelerationStructureDeviceAddressKHR 或者 vkGetAccelerationStructureHandleNV返回的设备地址 或者一个 VkAccelerationStructureKHR句柄
							accelerationStructureInstanceKHR.instanceCustomIndex = 0;//为用户自定义的24bit的索引（低24bit），可在ray shader中通过InstanceCustomIndexKHR访问
							accelerationStructureInstanceKHR.mask = 0xFF;//为该geometry的8bit的可视掩码（高8bit），只有在Cull Mask & instance.mask != 0情况下该instance才会被击中
							accelerationStructureInstanceKHR.instanceShaderBindingTableRecordOffset = 0;//为24bit（低24bit）的用于计算hit shader绑定表的索引的偏移值
							accelerationStructureInstanceKHR.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;//为应用到该instance的8bit（高8bit）的 VkGeometryInstanceFlagBitsKHR组合值掩码
							/*
							VkGeometryInstanceFlagBitsKHR（等价与VkGeometryInstanceFlagBitsNV）:
							VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR: 对该instance关闭face culling
							VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR: 指明反转该instance中geometry中的面的决定添加，因为facing在物体空间中定义，instance transform不会改变其面的方向，但geometry transform会。
							VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR:  对该instance强制使所有geometry的opaque flag 置位就像是设置了VK_GEOMETRY_OPAQUE_BIT_KHR一样，这种行为可以通过SPIR-V NoOpaqueKHR ray flag复写。
							VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR:  对该instance强制使所有geometry的opaque flag 不置位就像是没有设置VK_GEOMETRY_OPAQUE_BIT_KHR一样，这种行为可以通过SPIR-V OpaqueKHR ray flag复写。
							*/
							accelerationStructureInstanceKHR.transform = VkTransformMatrixKHR{/*假设这是一个有效的VkTransformMatrixKHR*/ };//为应用到加速结构的变换矩阵

							/*
							Acceleration structure  motion instances可以构建为一个top-level acceleration structures.每个instance是top-level acceleration structures中分离的组分，包含一个 bottom-level acceleration structure的在包含 运动类型以及决定 instance在时间上的运动的参数的变换位置处的所有geometry
							*/

							VkAccelerationStructureMotionInstanceNV accelerationStructureMotionInstanceNV{};
							accelerationStructureMotionInstanceNV.type = VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV;//为 VkAccelerationStructureMotionInstanceTypeNV值定义该motion instance的类型，指明union中哪个数据有效
							/*
							VkAccelerationStructureMotionInstanceTypeNV:
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_STATIC_NV: 指明这个instance是静态的没有任何instance移动
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MATRIX_MOTION_NV: 指明这个instance是一个motion instance，其移动通过两个矩阵间的插值指定
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV:  指明这个instance是一个motion instance，其移动通过SRT decomposition的插值指定
							*/
							accelerationStructureMotionInstanceNV.flags = 0;//当前未使用，但是需要来保证data中的自然内存排布对齐
							VkAccelerationStructureMotionInstanceDataNV accelerationStructureMotionInstanceDataNV{};//这是一个union
							{
								accelerationStructureMotionInstanceDataNV.staticInstance = accelerationStructureInstanceKHR;//包含static instance数据的VkAccelerationStructureInstanceKHR
								VkAccelerationStructureMatrixMotionInstanceNV accelerationStructureMatrixMotionInstanceNV{};
								{
									/*
									time 0到time 1之间的变换为: transformT0 × (1 - time) + transformT1 × time
									*/
									accelerationStructureMatrixMotionInstanceNV.accelerationStructureReference = 0;//为vkGetAccelerationStructureDeviceAddressKHR 或者 vkGetAccelerationStructureHandleNV返回的设备地址 或者一个 VkAccelerationStructureKHR句柄
									accelerationStructureMatrixMotionInstanceNV.flags = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR;//为应用到该instance的8bit（高8bit）的 VkGeometryInstanceFlagBitsKHR组合值掩码
									accelerationStructureMatrixMotionInstanceNV.instanceCustomIndex = 0;//为用户自定义的24bit的索引（低24bit），可在ray shader中通过InstanceCustomIndexKHR访问
									accelerationStructureMatrixMotionInstanceNV.mask = 0xFF;// 为该geometry的8bit的可视掩码（高8bit），只有在Cull Mask & instance.mask != 0情况下该instance才会被击中
									accelerationStructureMatrixMotionInstanceNV.instanceShaderBindingTableRecordOffset = 0;//为24bit（低24bit）的用于计算hit shader绑定表的索引的偏移值
									accelerationStructureMatrixMotionInstanceNV.transformT0 = VkTransformMatrixKHR{/*假设这是一个有效的VkTransformMatrixKHR*/ };//为一个描述应用到加速结构在time 0.0的变换的 VkTransformMatrixKHR
									accelerationStructureMatrixMotionInstanceNV.transformT1 = VkTransformMatrixKHR{/*假设这是一个有效的VkTransformMatrixKHR*/ };//为一个描述应用到加速结构在time 1.0的变换的 VkTransformMatrixKHR
								}
								accelerationStructureMotionInstanceDataNV.matrixMotionInstance = accelerationStructureMatrixMotionInstanceNV;//包含matrix motion instance数据的VkAccelerationStructureMatrixMotionInstanceNV
								VkAccelerationStructureSRTMotionInstanceNV accelerationStructureSRTMotionInstanceNV{};
								{
									/*
									time 0到time 1之间的变换为: transformT0 × (1 - time) + transformT1 × time
									*/
									accelerationStructureSRTMotionInstanceNV.accelerationStructureReference = 0;//为vkGetAccelerationStructureDeviceAddressKHR 或者 vkGetAccelerationStructureHandleNV返回的设备地址 或者一个 VkAccelerationStructureKHR句柄
									accelerationStructureSRTMotionInstanceNV.flags = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR;//为应用到该instance的8bit（高8bit）的 VkGeometryInstanceFlagBitsKHR组合值掩码
									accelerationStructureSRTMotionInstanceNV.instanceCustomIndex = 0;//为用户自定义的24bit的索引（低24bit），可在ray shader中通过InstanceCustomIndexKHR访问
									accelerationStructureSRTMotionInstanceNV.mask = 0xFF;//为该geometry的8bit的可视掩码（高8bit），只有在Cull Mask & instance.mask != 0情况下该instance才会被击中
									accelerationStructureSRTMotionInstanceNV.instanceShaderBindingTableRecordOffset = 0;//为24bit（低24bit）的用于计算hit shader绑定表的索引的偏移值
									VkSRTDataNV  SRTDataNV{};
									{
										/*
										VkSRTDataNV 定义第一个矩阵元素:
										S =    sx   a   b   pvx
											   0    sy  c   pvy
											   0    0   sz  pvz
										
										VkSRTDataNV 定义第二个四元数元素:
										R =    qx   qy   qz   qw	  其中定义为绕归一化的轴[ax,ay,zx] 旋转theta角度，则 [ qx, qy, qz ] = sin(theta/2) × [ ax, ay, az ] ，qw = cos(theta/2)

										VkSRTDataNV 定义第三个位移矩阵元素
										T =   1     0    0   tx
											  0     1    0   ty
											  0     0    1   tz

										VkSRTDataNV定义的最终变换为:  T × R × S 
										*/
										SRTDataNV.sx = 0;//为变换在x维上的缩放量
										SRTDataNV.a = 0;//为切变变换的一个分量
										SRTDataNV.b = 0;//为切变变换的一个分量
										SRTDataNV.pvx = 0;//为变换支点的x分量上的值
										SRTDataNV.sy = 0;//为变换在y维上的缩放量
										SRTDataNV.c = 0;//为切变变换的一个分量
										SRTDataNV.pvy = 0;//为变换支点的y分量上的值
										SRTDataNV.sz = 0;//为变换在z维上的缩放量
										SRTDataNV.pvz = 0;//为变换支点的z分量上的值
										SRTDataNV.qx = 0;//为四元数旋转的x分量值
										SRTDataNV.qy = 0;//为四元数旋转的y分量值
										SRTDataNV.qz = 0;//为四元数旋转的z分量值
										SRTDataNV.qw = 0;//为四元数旋转的w分量值
										SRTDataNV.tx = 0;//为旋转后平移的x分量值
										SRTDataNV.ty = 0;//为旋转后平移的y分量值
										SRTDataNV.tz = 0;//为旋转后平移的z分量值

									}
									accelerationStructureSRTMotionInstanceNV.transformT0 = SRTDataNV;//为一个描述应用到加速结构在time 0.0的变换的 VkSRTDataNV
									accelerationStructureSRTMotionInstanceNV.transformT1 = SRTDataNV;//为一个描述应用到加速结构在time 1.0的变换的 VkSRTDataNV
								}
								accelerationStructureMotionInstanceDataNV.srtMotionInstance = accelerationStructureSRTMotionInstanceNV;//为包含 SRT motion instance数据的 VkAccelerationStructureSRTMotionInstanceNV
							}

							accelerationStructureMotionInstanceNV.data = accelerationStructureMotionInstanceDataNV;//是一个VkAccelerationStructureMotionInstanceDataNV 包含该motion instance的数据


						}
						instanceDataKHR.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端const地址*//*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//如果arrayOfPointers 为VK_TRUE，则data指向一个数组，数组中每个元素是一个指向VkAccelerationStructureInstanceKHR 结构体的指针，否则data指向一个VkAccelerationStructureInstanceKHR 或者 VkAccelerationStructureMotionInstanceNV 结构体的数组
						instanceDataKHR.arrayOfPointers = VK_FALSE;//指明data是否用作是一组地址的数值或者就是一个数组
					}
					geometryDataKHR.instances = instanceDataKHR;// VkAccelerationStructureGeometryInstancesDataKHR 值 
				}
				geometryKHR.geometry = geometryDataKHR;// VkAccelerationStructureGeometryDataKHR的union值描述该加速结构引用的几何数据
			}
			accelerationStructureBuildGeometryInfoKHR.pGeometries = &geometryKHR;//一组VkAccelerationStructureGeometryKHR 数组指针
			accelerationStructureBuildGeometryInfoKHR.ppGeometries = VK_NULL_HANDLE;//一组VkAccelerationStructureGeometryKHR 数组指针的数组指针  ,和pGeometries 不能同时使用,必有一个为VK_NULL_HANDLE,shader中以 RayGeometryIndexKHR进行访问
			accelerationStructureBuildGeometryInfoKHR.scratchData = VkDeviceOrHostAddressKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressKHR*/ };//为用于构建的scratch的 device 或者 host端的内存地址
			/*
			VkAccelerationStructureBuildGeometryInfoKHR有效用法:
			1.type 不能为VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
			2.如果geometryCount 不为0，则pGeometries 或ppGeometries 必须有一个为有效的指针，另外一个为NULL
			3.如果type 为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR，则（1）pGeometries 或者 ppGeometries 中的geometryType 必须为VK_GEOMETRY_TYPE_INSTANCES_KHR
																		 （2）geometryCount 必须为1
			4.如果type 为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR，则（1）pGeometries 或者 ppGeometries 中的geometryType 不能为VK_GEOMETRY_TYPE_INSTANCES_KHR
																		    （2）pGeometries 或者 ppGeometries 中的所有geometry的geometryType必须相同
																		    （3）geometryCount 必须小于等于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxGeometryCount
																		    （4）如果pGeometries 或者 ppGeometries 中的所有geometry的geometryType为VK_GEOMETRY_TYPE_AABBS_KHR，则所有geometry中的AABBs 必须小于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPrimitiveCount
																		    （5）如果pGeometries 或者 ppGeometries 中的所有geometry的geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则所有geometry中的triangles 必须小于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPrimitiveCount
			5.如果flags含VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR，则flags不能含VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR
			6.如果dstAccelerationStructure 以VkAccelerationStructureCreateInfoKHR::flags中含VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV 创建，则flags中必须含有VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV
			7.如果flags中必须含有VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV，则dstAccelerationStructure 以VkAccelerationStructureCreateInfoKHR::flags中含VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV 创建
			8.如果flags中含VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV，则type 不能为VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
			9.如果flags中含VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT，则flags 不能再包含VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT

			*/


			//指定geometry中数据存储的内存偏移信息，如何获取和解释这些数据根据VkGeometryTypeKHR，指定内存的一定偏移处开始的数据具体是什么，参见p3259
			VkAccelerationStructureBuildRangeInfoKHR accelerationStructureBuildRangeInfoKHR{};
			accelerationStructureBuildRangeInfoKHR.firstVertex = 0;//为geometry的三角形图元的第一个顶点的索引
			accelerationStructureBuildRangeInfoKHR.primitiveCount = 1;//定义对应加速结构中geometry的图元数量
			accelerationStructureBuildRangeInfoKHR.primitiveOffset = 0;//指定图元数据在内存中的起始字节偏移量
			accelerationStructureBuildRangeInfoKHR.transformOffset = 0;//指定变换矩阵数据在内存中的起始字节偏移量
			/*
			VkAccelerationStructureBuildRangeInfoKHR有效用法:
			1.对于类型为VK_GEOMETRY_TYPE_TRIANGLES_KHR的geometries，（1）如果geometry 使用索引，则指向VkAccelerationStructureGeometryTrianglesDataKHR::indexData的primitiveOffset必须是VkAccelerationStructureGeometryTrianglesDataKHR::indexType字节大小的整数倍
																    （2）如果geometry不适用索引，则指向VkAccelerationStructureGeometryTrianglesDataKHR::vertexData的primitiveOffset必须是VkAccelerationStructureGeometryTrianglesDataKHR::vertexFormat分量的字节大小的整数倍
																    （3）则指向VkAccelerationStructureGeometryTrianglesDataKHR::transformData的transformOffset必须是16的整数倍
			2.对于类型为VK_GEOMETRY_TYPE_AABBS_KHR的geometries，则指向VkAccelerationStructureGeometryAabbsDataKHR::data的primitiveOffset必须是8的整数倍
			3.对于类型为VK_GEOMETRY_TYPE_INSTANCES_KHR的geometries，则指向VkAccelerationStructureGeometryInstancesDataKHR::data的primitiveOffset必须是16的整数倍
			*/
			
			VkAccelerationStructureBuildRangeInfoKHR* accelerationStructureBuildRangeInfoKHRPointer = &accelerationStructureBuildRangeInfoKHR;

			vkCmdBuildAccelerationStructuresKHR(commandBuffer, 1/*infoCount,指明要构建的加速结构的数量*/, &accelerationStructureBuildGeometryInfoKHR/*pInfos,infoCount个VkAccelerationStructureBuildGeometryInfoKHR 数组指针指明相关参数 */, &accelerationStructureBuildRangeInfoKHRPointer/*ppBuildRangeInfos，infoCount个VkAccelerationStructureBuildRangeInfoKHR指针的数组种指针指明pInfo中加速结构数据存储的动态偏移*/);//对srcAccelerationStructure，dstAccelerationStructure 以及scratchData的必须以VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage进行同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR 或者 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR进行访问,除此之外所有的buffer只能在相同阶段以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR访问，
			/*
			vkCmdBuildAccelerationStructuresKHR有效用法:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure特性必须开启
			2.pInfos中每个元素的mode必须是一个有效的VkBuildAccelerationStructureModeKHR值
			3.pInfos中任何srcAccelerationStructure不是VK_NULL_HANDLE的元素，其srcAccelerationStructure必须是一个有效的VkAccelerationStructureKHR 句柄
			4.对pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则该元素的srcAccelerationStructure不能为VK_NULL_HANDLE	
			5.对pInfos中任何元素的srcAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
			6.pInfos中任何元素的dstAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
			7.pInfos中任何元素的dstAccelerationStructure 必须是一个有效的VkAccelerationStructureKHR 句柄
			8.pInfos中每个元素，则（1）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
								  （2）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
								  （3）如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则srcAccelerationStructure中inactive primitives不能变为active的，active primitives不能变为inactive的
			9.pInfos中任何元素的dstAccelerationStructure不能被任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的元素的 geometry.instances.data引用
			10.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR  的元素的srcAccelerationStructure的内存范围重叠
			11.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的dstAccelerationStructure的内存范围重叠
			12.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的scratchData的内存范围重叠
			13.pInfos中任何元素的scratchData的内存范围不能和任何其他元素的scratchData的内存范围重叠
			14.pInfos中任何元素的scratchData的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR(包含相同元素)  的元素的srcAccelerationStructure元素的srcAccelerationStructure的内存范围重叠
			15.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的任何元素的 geometry.instances.data引用的加速结构的内存范围重叠
			16.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，（1）则srcAccelerationStructure必须在先前以VkAccelerationStructureBuildGeometryInfoKHR::flags设置有VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR 构建好了
																							  （2）则其srcAccelerationStructure 和dstAccelerationStructure 必须是同一个对象或者不含有任何memory aliasing
																							  （3）则其geometryCount 必须和srcAccelerationStructure最后一次构建的geometryCount相同
																							  （4）则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																							  （5）则其type 必须和srcAccelerationStructure最后一次构建的type相同
																							  （6）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其geometryType 必须和srcAccelerationStructure最后一次构建的geometryType相同
																							  （7）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																							  （8）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.vertexFormat 必须和srcAccelerationStructure最后一次构建的geometry.triangles.vertexFormat相同
																							  （9）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.maxVertex 必须和srcAccelerationStructure最后一次构建的geometry.triangles.maxVertex相同
																							  （10）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.indexType 必须和srcAccelerationStructure最后一次构建的geometry.triangles.indexType相同
																							  （11）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData为NULL则其geometry.triangles.transformData 必须为NULL 
																							  （12）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData不为NULL则其geometry.triangles.transformData 必须不为NULL 
																							  （13）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果其geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则每个引用的索引值必须和srcAccelerationStructure最后一次构建引用的索引值相同
																							  （14）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其对应的VkAccelerationStructureBuildRangeInfoKHR的primitiveCount 必须和srcAccelerationStructure最后一次构建的primitiveCount相同
																							  （15）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果该geometry使用索引indices，则其对应的VkAccelerationStructureBuildRangeInfoKHR的firstVertex 必须和srcAccelerationStructure最后一次构建的firstVertex 相同
			17.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries 每个以geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的元素，其对应的ppBuildRangeInfos[i][j].primitiveCount 必须小于等于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount
			18.对pInfos中的每个元素，用于创建dstAccelerationStructure的buffer必须绑定到VkDeviceMemory对象上
			19.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则用于创建dstAccelerationStructure的buffer必须绑定到VkDeviceMemory对象上
			20.对pInfos中的每个元素，用于创建被pGeometries 或者 ppGeometries中geometryType的VK_GEOMETRY_TYPE_INSTANCES_KHR 引用的acceleration structure的buffer必须绑定到VkDeviceMemory对象上
			21.如果pInfos[i].mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR 或者 VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则所有在pInfos[i].scratchData.deviceAddress到pInfos[i].scratchData.deviceAddress + N - 1 之间的地址必须是在同一个buffer的device address range内，其中N是vkGetAccelerationStructureBuildSizesKHR传入相同VkAccelerationStructureBuildGeometryInfoKHR以及primitive count  返回的VkAccelerationStructureBuildSizesInfoKHR结构中buildScratchSize成员的值
			22.任何其buffer device addresses 被pInfos[i].pGeometries 以及 pInfos[i].ppGeometries中的所有geometry.triangles.vertexData, geometry.triangles.indexData, geometry.triangles.transformData, geometry.aabbs.data, 以及 geometry.instances.data所指的buffer必须以VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR 创建
			23.任何其buffer device addresses 被 pInfos[i].scratchData.deviceAddress所指的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
			24.对pInfos中的每个元素，则（1）其scratchData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
									   （2）如果scratchData.deviceAddress是一个non-sparse的address，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
									   （3）其scratchData.deviceAddress 必须是VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment的倍数
			25.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR 的元素，则（1）geometry.triangles.vertexData.deviceAddress必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （2）如果geometry.triangles.vertexData.deviceAddress所对non-sparse 的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （3）geometry.triangles.vertexData.deviceAddress中必须对齐到vertexFormat中最小分量的字节数大小
																															   （4）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，如果geometry.triangles.indexData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 中必须对齐到indexType的字节数大小
																															   （7）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （8）如果geometry.triangles.transformData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （9）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 中必须对齐到16字节大小
			26.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_AABBS_KHR 的元素，则（1）geometry.aabbs.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																														   （2）如果geometry.aabbs.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																														   （3）geometry.aabbs.data.deviceAddress 必须对齐到8字节
			27.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR 的元素，则（1）如果geometry.arrayOfPointers 为VK_FALSE，则geometry.instances.data.deviceAddress 必须对齐到16字节
																															   （2）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress 必须对齐到8字节
																															   （3）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress内存中的每个元素必须对齐到16字节
																															   （4）geometry.instances.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.instances.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）geometry.instances.data.deviceAddress内存中的每个VkAccelerationStructureInstanceKHR::accelerationStructureReference 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address 或者0
			28.commandBuffer 不能是一个protected command buffer
			29.对pInfos[i]的每个元素，dstAccelerationStructure 必须以VkAccelerationStructureCreateInfoKHR::size大于等于查询返回的内存大小，见调用vkGetAccelerationStructureBuildSizesKHR，传入pBuildInfo = pInfos[i]以及pMaxPrimitiveCounts中每个元素要大于等于对应ppBuildRangeInfos[i][j].primitiveCount的值，j在[0,pInfos[i].geometryCount)
			30.ppBuildRangeInfos[i]的每个元素必须是一个有效的pInfos[i].geometryCount 个 VkAccelerationStructureBuildRangeInfoKHR 结构体指针数组的指针
			*/




			//构建 acceleration structures，其中一些参数从device中获取
			VkDeviceAddress parameDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };
			uint32_t paramStride{};
			uint32_t maxPrimitiveCount{};
			uint32_t* pMaxPrimitiveCount = &maxPrimitiveCount;
			vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, 1/*infoCount,指明要构建的加速结构的数量*/, &accelerationStructureBuildGeometryInfoKHR/*pInfos,infoCount个VkAccelerationStructureBuildGeometryInfoKHR 数组指针指明相关参数 */,
				&parameDeviceAddress/*pIndirectDeviceAddresses,为infoCount个 buffer device addresses，指向 pInfos[i].geometryCount VkAccelerationStructureBuildRangeInfoKHR指明加速结构数据存储的动态偏移*/, &paramStride/*pIndirectStrides,为infoCount个pIndirectDeviceAddresses中元素之间的字节步长.*/, &pMaxPrimitiveCount/*ppMaxPrimitiveCounts,为infoCount个指向pInfos[i].geometryCount个值的指针的数组指针指明每个geometry构建的最大的图元数量*/);// pIndirectDeviceAddresses在VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage中同步，以VK_ACCESS_INDIRECT_COMMAND_READ_BIT进行访问，其他的资源的同步和访问和 vkCmdBuildAccelerationStructuresKHR相同
			/*
			vkCmdBuildAccelerationStructuresIndirectKHR有效用法:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructureIndirectBuild特性必须开启
			2.pInfos中每个元素的mode必须是一个有效的VkBuildAccelerationStructureModeKHR值
			3.pInfos中任何srcAccelerationStructure不是VK_NULL_HANDLE的元素，其srcAccelerationStructure必须是一个有效的VkAccelerationStructureKHR 句柄
			4.对pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则该元素的srcAccelerationStructure不能为VK_NULL_HANDLE
			5.对pInfos中任何元素的srcAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
			6.pInfos中任何元素的dstAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
			7.pInfos中任何元素的dstAccelerationStructure 必须是一个有效的VkAccelerationStructureKHR 句柄
			8.pInfos中每个元素，则（1）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
								  （2）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
								  （3）如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则srcAccelerationStructure中inactive primitives不能变为active的，active primitives不能变为inactive的
			9.pInfos中任何元素的dstAccelerationStructure不能被任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的元素的 geometry.instances.data引用
			10.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR  的元素的srcAccelerationStructure的内存范围重叠
			11.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的dstAccelerationStructure的内存范围重叠
			12.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的scratchData的内存范围重叠
			13.pInfos中任何元素的scratchData的内存范围不能和任何其他元素的scratchData的内存范围重叠
			14.pInfos中任何元素的scratchData的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR(包含相同元素)  的元素的srcAccelerationStructure元素的srcAccelerationStructure的内存范围重叠
			15.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的任何元素的 geometry.instances.data引用的加速结构的内存范围重叠
			16.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，（1）则srcAccelerationStructure必须在先前以VkAccelerationStructureBuildGeometryInfoKHR::flags设置有VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR 构建好了
																							  （2）则其srcAccelerationStructure 和dstAccelerationStructure 必须是同一个对象或者不含有任何memory aliasing
																							  （3）则其geometryCount 必须和srcAccelerationStructure最后一次构建的geometryCount相同
																							  （4）则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																							  （5）则其type 必须和srcAccelerationStructure最后一次构建的type相同
																							  （6）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其geometryType 必须和srcAccelerationStructure最后一次构建的geometryType相同
																							  （7）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																							  （8）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.vertexFormat 必须和srcAccelerationStructure最后一次构建的geometry.triangles.vertexFormat相同
																							  （9）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.maxVertex 必须和srcAccelerationStructure最后一次构建的geometry.triangles.maxVertex相同
																							  （10）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.indexType 必须和srcAccelerationStructure最后一次构建的geometry.triangles.indexType相同
																							  （11）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData为NULL则其geometry.triangles.transformData 必须为NULL
																							  （12）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData不为NULL则其geometry.triangles.transformData 必须不为NULL
																							  （13）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果其geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则每个引用的索引值必须和srcAccelerationStructure最后一次构建引用的索引值相同
																							  （14）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其对应的VkAccelerationStructureBuildRangeInfoKHR的primitiveCount 必须和srcAccelerationStructure最后一次构建的primitiveCount相同
																							  （15）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果该geometry使用索引indices，则其对应的VkAccelerationStructureBuildRangeInfoKHR的firstVertex 必须和srcAccelerationStructure最后一次构建的firstVertex 相同
			17.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries 每个以geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的元素，其对应的ppBuildRangeInfos[i][j].primitiveCount 必须小于等于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount
			18.对pInfos中的每个元素，用于创建dstAccelerationStructure的buffer必须绑定到VkDeviceMemory对象上
			19.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则用于创建dstAccelerationStructure的buffer必须绑定到VkDeviceMemory对象上
			20.对pInfos中的每个元素，用于创建被pGeometries 或者 ppGeometries中geometryType的VK_GEOMETRY_TYPE_INSTANCES_KHR 引用的acceleration structure的buffer必须绑定到VkDeviceMemory对象上
			21.如果pInfos[i].mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR 或者 VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则所有在pInfos[i].scratchData.deviceAddress到pInfos[i].scratchData.deviceAddress + N - 1 之间的地址必须是在同一个buffer的device address range内，其中N是vkGetAccelerationStructureBuildSizesKHR传入相同VkAccelerationStructureBuildGeometryInfoKHR以及primitive count  返回的VkAccelerationStructureBuildSizesInfoKHR结构中buildScratchSize成员的值
			22.任何其buffer device addresses 被pInfos[i].pGeometries 以及 pInfos[i].ppGeometries中的所有geometry.triangles.vertexData, geometry.triangles.indexData, geometry.triangles.transformData, geometry.aabbs.data, 以及 geometry.instances.data所指的buffer必须以VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR 创建
			23.任何其buffer device addresses 被 pInfos[i].scratchData.deviceAddress所指的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
			24.对pInfos中的每个元素，则（1）其scratchData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
									   （2）如果scratchData.deviceAddress是一个non-sparse的address，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
									   （3）其scratchData.deviceAddress 必须是VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment的倍数
			25.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR 的元素，则（1）geometry.triangles.vertexData.deviceAddress必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （2）如果geometry.triangles.vertexData.deviceAddress所对non-sparse 的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （3）geometry.triangles.vertexData.deviceAddress中必须对齐到vertexFormat中最小分量的字节数大小
																															   （4）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，如果geometry.triangles.indexData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 中必须对齐到indexType的字节数大小
																															   （7）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （8）如果geometry.triangles.transformData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （9）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 中必须对齐到16字节大小
			26.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_AABBS_KHR 的元素，则（1）geometry.aabbs.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																														   （2）如果geometry.aabbs.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																														   （3）geometry.aabbs.data.deviceAddress 必须对齐到8字节
			27.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR 的元素，则（1）如果geometry.arrayOfPointers 为VK_FALSE，则geometry.instances.data.deviceAddress 必须对齐到16字节
																															   （2）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress 必须对齐到8字节
																															   （3）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress内存中的每个元素必须对齐到16字节
																															   （4）geometry.instances.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.instances.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）geometry.instances.data.deviceAddress内存中的每个VkAccelerationStructureInstanceKHR::accelerationStructureReference 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address 或者0
			28.commandBuffer 不能是一个protected command buffer
			29.对pIndirectDeviceAddresses中的任何元素，如果其buffer device address 对应是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
			30.对pIndirectDeviceAddresses[i]中的任何元素,所有在pIndirectDeviceAddresses[i] 到pIndirectDeviceAddresses[i] + (pInfos[i].geometryCount × pIndirectStrides[i]) - 1 的device addresse 必须在相同buffer的device address range内
			31.对pIndirectDeviceAddresses中的任何元素，其对应的buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
			32.pIndirectDeviceAddresses中的每个元素必须是4的倍数
			33.pIndirectStrides中的每个元素必须是4的倍数
			34.pIndirectDeviceAddresses中的任何元素引用的每个VkAccelerationStructureBuildRangeInfoKHR必须是一个有效的VkAccelerationStructureBuildRangeInfoKHR结构
			35.pInfos[i].dstAccelerationStructure 必须以VkAccelerationStructureCreateInfoKHR::size 大于等于查询构建操作返回的内存大小，见调用vkGetAccelerationStructureBuildSizesKHR 传入pBuildInfo = pInfos[i] 以及pMaxPrimitiveCounts = ppMaxPrimitiveCounts[i]
			36.每个ppMaxPrimitiveCounts[i][j]的值必须大于等于pIndirectDeviceAddresses[i] + (j × pIndirectStrides[i])定位的VkAccelerationStructureBuildRangeInfoKHR的primitiveCount
			
			*/

		}


		//Copying Acceleration Structures  参见p3260
		{
			/*
			有一个额外的命令，用于复制加速结构而不更新它们的内容。但在拷贝之前需要查询这个待拷贝的源加速结构的大小
			*/
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };


			//查询加速结构的大小参数KHR  ,对 pAccelerationStructures的加速结构以 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR pipeline stage 或者 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR访问
			//如果queryType为 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR,则查询返回压缩加速结构需要的字节大小，如果queryType为 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR，则查询返回序列化加速结构所需要的字节大小
			VkAccelerationStructureKHR accelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureKHR*/ };
			vkCmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, 1, &accelerationStructureKHR,
				VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType，指明查询类型*/, VkQueryPool{/*假设这是一个有效的VkQueryPool*/ }/*queryPool，指明管理结果的query pool*/, 0/*firstQuery,为存放加速结构查询结果的第一个query的索引*/);
			/*
			vkCmdWriteAccelerationStructuresPropertiesKHR有效用法:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
			2.queryPool 必须以匹配queryType创建
			3.由queryPool 以及firstQuery指定的queries必须是unavailable的
			4.用来创建pAccelerationStructures中每个加速结构的buffer必须已经绑定到device memory 上
			5.firstQuery + accelerationStructureCount 必须小于等于queryPool中queries的数量
			6.pAccelerationStructures中的所有加速结构必须已经在该命令的执行前构建
			7.pAccelerationStructures中的所有加速结构如果queryType为VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR则必须以VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR创建
			8.queryType必须为VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR,
							 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR,
							 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR, 或者
							 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR

			*/


			//查询加速结构的大小参数NV  ,对 pAccelerationStructures的访问以 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR访问
			VkAccelerationStructureNV accelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV*/ };
			vkCmdWriteAccelerationStructuresPropertiesNV(commandBuffer, 1, &accelerationStructureNV,
				VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV/*queryType，指明查询类型*/, VkQueryPool{/*假设这是一个有效的VkQueryPool*/ }/*queryPool，指明管理结果的query pool*/, 0/*firstQuery,为存放加速结构查询结果的第一个query的索引*/);
			/*
			vkCmdWriteAccelerationStructuresPropertiesNV有效用法:
			1.queryPool 必须以匹配queryType创建
			2.由queryPool 以及firstQuery指定的queries必须是unavailable的
			3.用来创建pAccelerationStructures中每个加速结构的buffer必须已经通过 vkBindAccelerationStructureMemoryNV绑定到device memory 上
			4.pAccelerationStructures中的所有加速结构必须已经在该命令的执行前构建
			5.pAccelerationStructures中的所有加速结构如果queryType为VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV则必须以VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR创建
			6.queryType必须为VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV

			*/


			//拷贝一个加速结构   ,对src 或者dst 以 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR pipeline stage 或者 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR 或者 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR访问
			vkCmdCopyAccelerationStructureNV(commandBuffer,
				VkAccelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV*/ }/*dst,为拷贝的dst 加速结构*/,
				VkAccelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV*/ }/*src,为拷贝的src 加速结构*/,
				VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR/*mode,为 VkCopyAccelerationStructureModeKHR值指明拷贝过程中的额外操作*/);
			/*
			vkCmdCopyAccelerationStructureNV有效用法:
			1.mode 必须为VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR或者 VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR
			2.src 加速结构必须在该命令执行前被构建
			3.如果mode为VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR ，src 加速结构必须以VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR 构建
			4.用于创建src，dst加速结构的buffer必须已经绑定到device memory 上
			5.该命令访问的dst底层的memory 范围不能和src底层的memory 范围有重叠
			6.dst必须已经通过vkBindAccelerationStructureMemoryNV绑定到一个完整的连续的单独的VkDeviceMemory上了
			*/


			VkCopyAccelerationStructureInfoKHR copyAccelerationStructureInfoKHR{};
			copyAccelerationStructureInfoKHR.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR;
			copyAccelerationStructureInfoKHR.pNext = nullptr;
			copyAccelerationStructureInfoKHR.mode = VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR;/*为 VkCopyAccelerationStructureModeKHR值指明拷贝过程中的额外操作
			VkCopyAccelerationStructureModeKHR （等同于VkCopyAccelerationStructureModeNV）:
			VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR: 创建一个用src到dst加速结构的直接拷贝，如果src包含一个别的加速结构的引用，则dst也会包含一个对相同加速结构的引用
			VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR:  创建一个更紧凑的src到dst的拷贝，dst加速结构必须至少以调用 vkCmdWriteAccelerationStructuresPropertiesKHR 或者 vkWriteAccelerationStructuresPropertiesKHR传入src返回的大小创建，如果src包含一个别的加速结构的引用，则dst也会包含一个对相同加速结构的引用
			VK_COPY_ACCELERATION_STRUCTURE_MODE_SERIALIZE_KHR:  以一种semi-opaque format序列化src加速结构（序列化的头部信息格式见p3720），存到dst加速结构中可以被一个兼容的实现重新加载
			VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR:  反序列化一个semi-opaque format的src加速结构，存到dst加速结构中
			*/
			copyAccelerationStructureInfoKHR.dst = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureNV*/ };//为拷贝的dst 加速结构
			copyAccelerationStructureInfoKHR.src = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureNV*/ };//为拷贝的src 加速结构
			/*
			VkCopyAccelerationStructureInfoKHR有效用法:
			1.mode 必须为VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR或者 VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR
			2.src 加速结构必须在该命令执行前被构建
			3.如果mode为VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR ，src 加速结构必须以VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR 构建
			4.用于创建src，dst加速结构的buffer必须已经绑定到device memory 上
			5.该命令访问的dst底层的memory 范围不能和src底层的memory 范围有重叠
			*/

			//拷贝一个加速结构NV   ,对pInfo->src 或者pInfo->dst 以 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR pipeline stage 或者 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步，以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR 或者 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR访问
			vkCmdCopyAccelerationStructureKHR(commandBuffer, &copyAccelerationStructureInfoKHR/*pInfo*/);
			/*
			vkCmdCopyAccelerationStructureNV有效用法:
			1. VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure特性必须开启
			2.用于创建pInfo->src，pInfo->dst加速结构的buffer必须已经绑定到device memory 上
			*/



			VkCopyAccelerationStructureToMemoryInfoKHR copyAccelerationStructureToMemoryInfoKHR{};
			copyAccelerationStructureToMemoryInfoKHR.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR;
			copyAccelerationStructureToMemoryInfoKHR.pNext = nullptr;
			copyAccelerationStructureToMemoryInfoKHR.dst = VkDeviceOrHostAddressKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressKHR*/ };//为用于拷贝的dst memory的 device 或者 host端的内存地址
			copyAccelerationStructureToMemoryInfoKHR.mode = VK_COPY_ACCELERATION_STRUCTURE_MODE_SERIALIZE_KHR;//为 VkCopyAccelerationStructureModeKHR值指明拷贝过程中的额外操作
			copyAccelerationStructureToMemoryInfoKHR.src = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureNV*/ };//为拷贝的src 加速结构
			/*
			VkCopyAccelerationStructureToMemoryInfoKHR有效用法:
			1.src 加速结构必须在该命令执行前被构建
			2.dst所指的memory的大小至少要和src加速结构的序列化大小一样大，参见vkWriteAccelerationStructuresPropertiesKHR 或者vkCmdWriteAccelerationStructuresPropertiesKHR传入queryType为VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR以及src加速结构
			3.mode 必须为VK_COPY_ACCELERATION_STRUCTURE_MODE_SERIALIZE_KHR
			*/
			
			
			/*
			拷贝一个加速结构序列化到device memory ，和vkCopyAccelerationStructureToMemoryKHR产生相同结果，只不过该命令会将结果写到device memory中，其输出可以被vkCmdCopyMemoryToAccelerationStructureKHR 或者 vkCopyMemoryToAccelerationStructureKHR使用
			对pInfo->src 或者pInfo->dst 以 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR pipeline stage 或者 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步
			
			对pInfo->src以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR访问，对pInfo->dst.deviceAddress以 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR访问
			
			对应句柄通过vkGetAccelerationStructureDeviceAddressKHR 或者 vkGetAccelerationStructureHandleNV获取
			*/
			vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, &copyAccelerationStructureToMemoryInfoKHR);
			/*
			vkCmdCopyAccelerationStructureToMemoryKHR有效用法:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
			2.pInfo->dst.deviceAddress 必须是一个有效的绑定到device memory的device address，且必须对齐到256字节
			3.如果pInfo->dst.deviceAddress所指的buffer是non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			4.创建pInfo->src的buffer必须已经绑定到device memory上
			*/
			
			
			
			
			VkCopyMemoryToAccelerationStructureInfoKHR copyMemoryToAccelerationStructureInfoKHR{};
			copyMemoryToAccelerationStructureInfoKHR.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR;
			copyMemoryToAccelerationStructureInfoKHR.pNext = nullptr;
			copyMemoryToAccelerationStructureInfoKHR.src = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为用于拷贝的src memory的 device 或者 host端的const内存地址
			copyMemoryToAccelerationStructureInfoKHR.dst = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureNV*/ };//为拷贝的dst 加速结构
			copyMemoryToAccelerationStructureInfoKHR.mode = VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR;//为 VkCopyAccelerationStructureModeKHR值指明拷贝过程中的额外操作
			/*
			VkCopyMemoryToAccelerationStructureInfoKHR有效用法:
			1.src所指的memory必须包含前线使用vkCmdCopyAccelerationStructureToMemoryKHR序列化的数据
			2.mode 必须为VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR
			3.src中的数据必须含有一个和vkGetDeviceAccelerationStructureCompatibilityKHR返回的和destination physical device兼容的format
			4.dst 必须以字节大小大于等于src序列化数据的大小创建
			*/
			
			
			/*
			拷贝device memory反序列化到一个加速结构 ，和vkCopyAccelerationStructureToMemoryKHR产生相同结果，只不过该命令也会将拷贝结果的写到device memory中
			对pInfo->src 或者pInfo->dst 以 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR pipeline stage 或者 VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage同步
			
			对pInfo->src.deviceAddress以VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR访问，对pInfo->dst以 VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR访问
			
			该命令可以接受来自vkCmdCopyAccelerationStructureToMemoryKHR 或者 vkCopyAccelerationStructureToMemoryKHR产生的加速结构
			*/
			vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, &copyMemoryToAccelerationStructureInfoKHR);
			/*
			vkCmdCopyMemoryToAccelerationStructureKHR有效用法:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
			2.pInfo->src.deviceAddress 必须是一个有效的绑定到device memory的device address，且必须对齐到256字节
			3.如果pInfo->src.deviceAddress所指的buffer是non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			4.创建pInfo->dst的buffer必须已经绑定到device memory上
			
			*/
			
			
			
			VkAccelerationStructureVersionInfoKHR accelerationStructureVersionInfoKHR{};
			accelerationStructureVersionInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR;
			accelerationStructureVersionInfoKHR.pNext = nullptr;
			uint8_t version = 0;
			accelerationStructureVersionInfoKHR.pVersionData = &version;//为vkCmdCopyAccelerationStructureToMemoryKHR中描述的定义在加速结构中的版本头信息的指针，该指针指向2×VK_UUID_SIZE 个uint8_t值
			
			VkAccelerationStructureCompatibilityKHR accelerationStructureCompatibilityKHR{};
			
			//检查序列化的加速结构是否和当前device兼容
			vkGetDeviceAccelerationStructureCompatibilityKHR(device, &accelerationStructureVersionInfoKHR, &accelerationStructureCompatibilityKHR/*pCompatibility,返回兼容信息*/);//VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
			VkAccelerationStructureCompatibilityKHR& accelerationStructureCompatibilityKHRRetured = accelerationStructureCompatibilityKHR;//
			/*
			VkAccelerationStructureCompatibilityKHR:
			VK_ACCELERATION_STRUCTURE_COMPATIBILITY_COMPATIBLE_KHR: 指明加速结构的版本信息和device兼容
			VK_ACCELERATION_STRUCTURE_COMPATIBILITY_INCOMPATIBLE_KHR: 指明加速结构的版本信息和device不兼容
			
			
			*/
		}

	}

	//Host Acceleration Structure Operations  参见p3277
	{
		/*
		如果 accelerationStructureHostCommands特性开启，则实现也提供了在host端对加速结构的操作:

		host端											对应            device端
		vkBuildAccelerationStructuresKHR				->				vkCmdBuildAccelerationStructuresKHR
		vkCopyAccelerationStructureKHR					->				vkCmdCopyAccelerationStructureKHR
		vkCopyAccelerationStructureToMemoryKHR			->				vkCmdCopyAccelerationStructureToMemoryKHR
		vkCopyMemoryToAccelerationStructureKHR			->				vkCmdCopyMemoryToAccelerationStructureKHR
		vkWriteAccelerationStructuresPropertiesKHR		->				vkCmdWriteAccelerationStructuresPropertiesKHR
		
		host端操作加速结构的命令访问的加速结构必须绑定到host-visible的内存，且所有加速结构构建的所有输入数据必须引用host端的地址而不是device端
		*/


		VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{/*假设这是一个有效的VkAccelerationStructureBuildGeometryInfoKHR*/};//前面已经描述过这里不再复述
		VkAccelerationStructureBuildRangeInfoKHR accelerationStructureBuildRangeInfoKHR{/*假设这是一个有效的VkAccelerationStructureBuildRangeInfoKHR*/ };//前面已经描述过这里不再复述
		const VkAccelerationStructureBuildRangeInfoKHR* accelerationStructureBuildRangeInfoKHRP = &accelerationStructureBuildRangeInfoKHR;
		
		//在host端构建加速结构  ,等效于vkCmdBuildAccelerationStructuresKHR，参数详解见前面的描述，这里不再复述，该命令不会进行任何内存访问控制
		vkBuildAccelerationStructuresKHR(device, VkDeferredOperationKHR{/*假设这是一个有效的VkDeferredOperationKHR*/ }, 1, & accelerationStructureBuildGeometryInfoKHR,& accelerationStructureBuildRangeInfoKHRP);
		/*
		vkBuildAccelerationStructuresKHR有效用法:
		1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructureHostCommands特性必须开启
		2.pInfos中每个元素的mode必须是一个有效的VkBuildAccelerationStructureModeKHR值
		3.pInfos中任何srcAccelerationStructure不是VK_NULL_HANDLE的元素，其srcAccelerationStructure必须是一个有效的VkAccelerationStructureKHR 句柄
		4.对pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则该元素的srcAccelerationStructure不能为VK_NULL_HANDLE
		5.对pInfos中任何元素的srcAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
		6.pInfos中任何元素的dstAccelerationStructure 不能和任何其他元素的dstAccelerationStructure 相同
		7.pInfos中任何元素的dstAccelerationStructure 必须是一个有效的VkAccelerationStructureKHR 句柄
		8.pInfos中每个元素，则（1）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
							  （2）如果其type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR，则其dstAccelerationStructure必须VkAccelerationStructureCreateInfoKHR::type为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR 或者 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR创建
							  （3）如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则srcAccelerationStructure中inactive primitives不能变为active的，active primitives不能变为inactive的
		9.pInfos中任何元素的dstAccelerationStructure不能被任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的元素的 geometry.instances.data引用
		10.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR  的元素的srcAccelerationStructure的内存范围重叠
		11.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的dstAccelerationStructure的内存范围重叠
		12.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的scratchData的内存范围重叠
		13.pInfos中任何元素的scratchData的内存范围不能和任何其他元素的scratchData的内存范围重叠
		14.pInfos中任何元素的scratchData的内存范围不能和任何其他mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR(包含相同元素)  的元素的srcAccelerationStructure元素的srcAccelerationStructure的内存范围重叠
		15.pInfos中任何元素的dstAccelerationStructure的内存范围不能和任何其他元素的geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的  pGeometries或者 ppGeometries中的任何元素的 geometry.instances.data引用的加速结构的内存范围重叠
		16.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，（1）则srcAccelerationStructure必须在先前以VkAccelerationStructureBuildGeometryInfoKHR::flags设置有VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR 构建好了
																						  （2）则其srcAccelerationStructure 和dstAccelerationStructure 必须是同一个对象或者不含有任何memory aliasing
																						  （3）则其geometryCount 必须和srcAccelerationStructure最后一次构建的geometryCount相同
																						  （4）则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																						  （5）则其type 必须和srcAccelerationStructure最后一次构建的type相同
																						  （6）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其geometryType 必须和srcAccelerationStructure最后一次构建的geometryType相同
																						  （7）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构， 则其flags 必须和srcAccelerationStructure最后一次构建的flags相同
																						  （8）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.vertexFormat 必须和srcAccelerationStructure最后一次构建的geometry.triangles.vertexFormat相同
																						  （9）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.maxVertex 必须和srcAccelerationStructure最后一次构建的geometry.triangles.maxVertex相同
																						  （10）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其geometry.triangles.indexType 必须和srcAccelerationStructure最后一次构建的geometry.triangles.indexType相同
																						  （11）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData为NULL则其geometry.triangles.transformData 必须为NULL
																						  （12）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果srcAccelerationStructure最后一次构建的geometry.triangles.transformData不为NULL则其geometry.triangles.transformData 必须不为NULL
																						  （13）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，如果其geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则每个引用的索引值必须和srcAccelerationStructure最后一次构建引用的索引值相同
																						  （14）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果geometryType 为VK_GEOMETRY_TYPE_TRIANGLES_KHR，则其对应的VkAccelerationStructureBuildRangeInfoKHR的primitiveCount 必须和srcAccelerationStructure最后一次构建的primitiveCount相同
																						  （15）对每个被其pGeometries 或者ppGeometries 引用的VkAccelerationStructureGeometryKHR结构，如果该geometry使用索引indices，则其对应的VkAccelerationStructureBuildRangeInfoKHR的firstVertex 必须和srcAccelerationStructure最后一次构建的firstVertex 相同
		17.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries 每个以geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR的元素，其对应的ppBuildRangeInfos[i][j].primitiveCount 必须小于等于VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount
		18.对pInfos[i]的每个元素，dstAccelerationStructure 必须以VkAccelerationStructureCreateInfoKHR::size 大于等于查询构建操作返回的内存大小，见调用vkGetAccelerationStructureBuildSizesKHR 传入pBuildInfo = pInfos[i] 以及pMaxPrimitiveCounts中的每个元素大于等于对应的ppBuildRangeInfos[i][j].primitiveCount，其中j处于 [0,pInfos[i].geometryCount)
		19.ppBuildRangeInfos[i]中的每个元素必须是有效的pInfos[i].geometryCount个VkAccelerationStructureBuildRangeInfoKHR数组的指针
		20.任何deferredOperation关联的之前的deferred operation 必须已经完成
		21.pInfos中每个元素，创建其dstAccelerationStructure的buffer必须绑定到host-visible device memory上
		22.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则用于创建srcAccelerationStructure的buffer必须绑定到host-visible device memory上
		23.对pInfos中的每个元素，用于创建被pGeometries 或者 ppGeometries中geometryType的VK_GEOMETRY_TYPE_INSTANCES_KHR 引用的acceleration structure的buffer必须绑定到host-visible device memory上
		24.如果pInfos[i].mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ，则所有在pInfos[i].scratchData.hostAddress到pInfos[i].scratchData.hostAddress + N - 1 之间的地址必须是在valid host memory，其中N是vkGetAccelerationStructureBuildSizesKHR传入相同VkAccelerationStructureBuildGeometryInfoKHR以及primitive count  返回的VkAccelerationStructureBuildSizesInfoKHR结构中buildScratchSize成员的值
		25.如果pInfos[i].mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR ，则所有在pInfos[i].scratchData.hostAddress到pInfos[i].scratchData.hostAddress + N - 1 之间的地址必须是在valid host memory，其中N是vkGetAccelerationStructureBuildSizesKHR传入相同VkAccelerationStructureBuildGeometryInfoKHR以及primitive count  返回的VkAccelerationStructureBuildSizesInfoKHR结构中updateScratchSize成员的值
		26.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR 的元素，则（1） geometry.triangles.vertexData.hostAddress必须是一个有效的host address
																														   （2）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.hostAddress 必须是一个有效的host address
																														   （3）如果geometry.triangles.transformData.hostAddress 不为0，则geometry.triangles.transformData.hostAddress 必须是一个有效的host address
		27.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_AABBS_KHR 的元素，则geometry.aabbs.data.hostAddress 必须是一个有效的host address
		28.

		
		19.pInfos中每个元素，如果其mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则用于创建dstAccelerationStructure的buffer必须绑定到VkDeviceMemory对象上
			20.对pInfos中的每个元素，用于创建被pGeometries 或者 ppGeometries中geometryType的VK_GEOMETRY_TYPE_INSTANCES_KHR 引用的acceleration structure的buffer必须绑定到VkDeviceMemory对象上
			21.如果pInfos[i].mode为VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR 或者 VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR，则所有在pInfos[i].scratchData.deviceAddress到pInfos[i].scratchData.deviceAddress + N - 1 之间的地址必须是在同一个buffer的device address range内，其中N是vkGetAccelerationStructureBuildSizesKHR传入相同VkAccelerationStructureBuildGeometryInfoKHR以及primitive count  返回的VkAccelerationStructureBuildSizesInfoKHR结构中buildScratchSize成员的值
			22.任何其buffer device addresses 被pInfos[i].pGeometries 以及 pInfos[i].ppGeometries中的所有geometry.triangles.vertexData, geometry.triangles.indexData, geometry.triangles.transformData, geometry.aabbs.data, 以及 geometry.instances.data所指的buffer必须以VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR 创建
			23.任何其buffer device addresses 被 pInfos[i].scratchData.deviceAddress所指的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
			24.对pInfos中的每个元素，则（1）其scratchData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
									   （2）如果scratchData.deviceAddress是一个non-sparse的address，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
									   （3）其scratchData.deviceAddress 必须是VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment的倍数
			25.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR 的元素，则（1）geometry.triangles.vertexData.deviceAddress必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （2）如果geometry.triangles.vertexData.deviceAddress所对non-sparse 的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （3）geometry.triangles.vertexData.deviceAddress中必须对齐到vertexFormat中最小分量的字节数大小
																															   （4）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，如果geometry.triangles.indexData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）如果geometry.triangles.indexType 不为VK_INDEX_TYPE_NONE_KHR，则geometry.triangles.indexData.deviceAddress 中必须对齐到indexType的字节数大小
																															   （7）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （8）如果geometry.triangles.transformData.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （9）如果geometry.triangles.transformData.deviceAddress 不为0，则geometry.triangles.transformData.deviceAddress 中必须对齐到16字节大小
			26.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_AABBS_KHR 的元素，则（1）geometry.aabbs.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																														   （2）如果geometry.aabbs.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																														   （3）geometry.aabbs.data.deviceAddress 必须对齐到8字节
			27.对pInfos[i].pGeometries 或者 pInfos[i].ppGeometries中任何geometryType为VK_GEOMETRY_TYPE_INSTANCES_KHR 的元素，则（1）如果geometry.arrayOfPointers 为VK_FALSE，则geometry.instances.data.deviceAddress 必须对齐到16字节
																															   （2）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress 必须对齐到8字节
																															   （3）如果geometry.arrayOfPointers 为VK_TRUE，则geometry.instances.data.deviceAddress内存中的每个元素必须对齐到16字节
																															   （4）geometry.instances.data.deviceAddress 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address
																															   （5）如果geometry.instances.data.deviceAddress 是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
																															   （6）geometry.instances.data.deviceAddress内存中的每个VkAccelerationStructureInstanceKHR::accelerationStructureReference 必须是一个有效的通过vkGetBufferDeviceAddress获取的device address 或者0
			28.commandBuffer 不能是一个protected command buffer
			29.对pIndirectDeviceAddresses中的任何元素，如果其buffer device address 对应是一个non-sparse的buffer，则该buffer必须绑定到一个完整的连续的单独的VkDeviceMemory对象上
			30.对pIndirectDeviceAddresses[i]中的任何元素,所有在pIndirectDeviceAddresses[i] 到pIndirectDeviceAddresses[i] + (pInfos[i].geometryCount × pIndirectStrides[i]) - 1 的device addresse 必须在相同buffer的device address range内
			31.对pIndirectDeviceAddresses中的任何元素，其对应的buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
			32.pIndirectDeviceAddresses中的每个元素必须是4的倍数
			33.pIndirectStrides中的每个元素必须是4的倍数
			34.pIndirectDeviceAddresses中的任何元素引用的每个VkAccelerationStructureBuildRangeInfoKHR必须是一个有效的VkAccelerationStructureBuildRangeInfoKHR结构
			35.pInfos[i].dstAccelerationStructure 必须以VkAccelerationStructureCreateInfoKHR::size 大于等于查询构建操作返回的内存大小，见调用vkGetAccelerationStructureBuildSizesKHR 传入pBuildInfo = pInfos[i] 以及pMaxPrimitiveCounts = ppMaxPrimitiveCounts[i]
			36.每个ppMaxPrimitiveCounts[i][j]的值必须大于等于pIndirectDeviceAddresses[i] + (j × pIndirectStrides[i])定位的VkAccelerationStructureBuildRangeInfoKHR的primitiveCount




• VUID-vkBuildAccelerationStructuresKHR-pInfos-03775
For each element of pInfos, the buffer used to create its dstAccelerationStructure member
must be bound to memory that was not allocated with multiple instances
• VUID-vkBuildAccelerationStructuresKHR-pInfos-03776
For each element of pInfos, if its mode member is
VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR the buffer used to create its
srcAccelerationStructure member must be bound to memory that was not allocated with
multiple instances
3284
• VUID-vkBuildAccelerationStructuresKHR-pInfos-03777
For each element of pInfos, the buffer used to create each acceleration structure
referenced by the geometry.instances.data member of any element of pGeometries or
ppGeometries with a geometryType of VK_GEOMETRY_TYPE_INSTANCES_KHR must be bound to
memory that was not allocated with multiple instances
• VUID-vkBuildAccelerationStructuresKHR-pInfos-03778
For any element of pInfos[i].pGeometries or pInfos[i].ppGeometries with a geometryType of
VK_GEOMETRY_TYPE_INSTANCES_KHR, geometry.instances.data.hostAddress must be a valid
host address
• VUID-vkBuildAccelerationStructuresKHR-pInfos-03779
For any element of pInfos[i].pGeometries or pInfos[i].ppGeometries with a geometryType of
VK_GEOMETRY_TYPE_INSTANCES_KHR, each VkAccelerationStructureInstanceKHR
::accelerationStructureReference value in geometry.instances.data.hostAddress must be a
valid VkAccelerationStructureKHR object
• VUID-vkBuildAccelerationStructuresKHR-pInfos-04930
For any element of pInfos[i].pGeometries or pInfos[i].ppGeometries with a geometryType of
VK_GEOMETRY_TYPE_INSTANCES_KHR with VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV set,
each accelerationStructureReference in any structure in
VkAccelerationStructureMotionInstanceNV value in geometry.instances.data.hostAddress
must be a valid VkAccelerationStructureKHR object
		*/


	}
}

NS_TEST_END