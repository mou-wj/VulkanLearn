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
	deferred operations ����Ӧ�ú�����ʹ��Ӧ�ù�����̳߳�ȥ�����ͬ����ʱ�����host�˵���� VK_KHR_deferred_host_operations��չ������һЩ֧����Щhost������Ļ������ƣ�ֻ�����������չ��host����������ӳ�ִ��
	
	*/


	//Requesting Deferral   �������defer�����Լ���Ҫ��ѭ��һЩ����ĸ��� �μ�p3196

	//Deferred Host Operations API  �μ�p3197
	{

		VkDeferredOperationKHR/*�ýṹ�������defered command��ִ��״̬*/  deferredOperationKHR{};

		//����һ��׷��defered command��VkDeferredOperationKHR����
		vkCreateDeferredOperationKHR(device, nullptr, &deferredOperationKHR);

		//��һ��defered command����һ���̣߳��ýӿ����߳��е���
		VkResult deferredOperationJoinResult =  vkDeferredOperationJoinKHR(device, deferredOperationKHR);
		deferredOperationJoinResult;
		/*
		VK_SUCCESS:  ָ��defered �����Ѿ���ɣ�Ӧ�ÿ��Ե���vkGetDeferredOperationResultKHR��ȡ��״̬
		VK_THREAD_DONE_KHR:  ָ��defered ������δ��ɵ�������ɣ��Ѿ�û�б�Ĺ������԰��Ÿ��߳��ˣ�������������vkDeferredOperationJoinKHR�ǲ���Ҫ���һ�Ӱ������
		VK_THREAD_IDLE_KHR:  ָ��defered ������δ���,�����ڵ��øú�����ʱ��û�б�Ĺ������԰��Ÿ��̣߳��������˵��defered ������ִ��������һ��������ƽ�е��ȵļ��٣�������������vkDeferredOperationJoinKHR�ǿ��Ե�		
		*/

		//��defered command��ɣ�������VkDeferredOperationKHR����
		vkDestroyDeferredOperationKHR(device, deferredOperationKHR, nullptr);
		/*
		vkDestroyDeferredOperationKHR��Ч�÷�:
		1.�������ʱ�ṩ��VkAllocationCallbacks������������ṩ��֮���ݵ�callbacks
		2.�������ʱû���ṩVkAllocationCallbacks��������pAllocator���봫��NULL
		3.operation�����Ѿ����
		*/

		//��ѯ�������ж��ٸ��߳�ͨ��vkDeferredOperationJoinKHR���ȴ�defered command�����  ,�������pow(2,32) -1 ���ʾ���ܹ��Ƹ���Ҫ���ٸ��̣߳���������ӿ��ڿ�ʼ��ʱ�����һ��
		uint32_t numThreadNeeded = vkGetDeferredOperationMaxConcurrencyKHR(device, deferredOperationKHR);


		//��ȡdefered command��ִ�еĽ������˵ִ��״̬
		VkResult completedResult = vkGetDeferredOperationResultKHR(device, deferredOperationKHR);

	}


}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::PrivateDataTest()
{
	/*
	private data ��չ�ṩ��һ�ַ�ʽ�������û��Լ���������ݹ�����vulkan�Ķ����У����ֹ�����ͨ����˽�����ݲ��д洢�û��������ݵ�64λ�޷�����������ɵġ�˽�����ݲ۱�ʾ�豸��ÿ���Ӷ����һ��������Ĵ洢����
	
	device�����ڴ���ʱ���������ݲۣ�ͨ���� VkDeviceCreateInfo.pNext���������������� VkDevicePrivateDataCreateInfo
	*/

	VkPrivateDataSlot privateDataSlot{};//�ȼ���VkPrivateDataSlotEXT

	//����һ��˽�����ݲ�,  ��ͬ��vkCreatePrivateDataSlotEXT
	VkPrivateDataSlotCreateInfo privateDataSlotCreateInfo{};//�ȼ���VkPrivateDataSlotCreateInfoEXT
	privateDataSlotCreateInfo.sType = VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO;
	privateDataSlotCreateInfo.pNext = nullptr;
	privateDataSlotCreateInfo.flags = 0;//����δ��ʹ��

	vkCreatePrivateDataSlot(device, &privateDataSlotCreateInfo, nullptr, &privateDataSlot);// privateData ���Ա��뿪��


	//�洢�û���������ݵ�һ��������vulkan�����˽�����ݲ���,  ��ͬ��vkSetPrivateDataEXT
	vkSetPrivateData(device, VK_OBJECT_TYPE_BUFFER/*objectType��ָ��������vulkan���������*/, (uint64_t)VkBuffer {/*��������һ����Ч��VkBuffer*/ }/* objectHandle��Ϊ�����Ķ���ľ��,����Ϊdevice���ߴ�device�д�������Ķ�ӦobjectType�ľ��*/,
		privateDataSlot/* privateDataSlot��VkPrivateDataSlot���ָ��private data�洢��λ��*/, 1234567890/*data���û�����Ĺ�����vulkan�����ݣ� �洢��privateDataSlot��*/);

	//��һ��������vulkan�����˽�����ݲ��л�ȡ�û����������,  ��ͬ��vkGetPrivateDataEXT
	uint64_t privateData = 0;
	vkGetPrivateData(device, VK_OBJECT_TYPE_BUFFER/*objectType��ָ��������vulkan���������*/, (uint64_t)VkBuffer {/*��������һ����Ч��VkBuffer*/ }/* objectHandle��Ϊ�����Ķ���ľ��,����Ϊdevice���ߴ�device�д�������Ķ�ӦobjectType�ľ��*/,
		privateDataSlot/* privateDataSlot��VkPrivateDataSlot���ָ��private data�洢��λ��*/, & privateData/*pData�����ع�����vulkan�Ĵ洢��privateDataSlot���û���������ݣ����֮ǰû�������򷵻�0 */);



	//����˽�����ݲ�   ����ͬ��vkDestroyPrivateDataSlotEXT
	vkDestroyPrivateDataSlot(device, privateDataSlot, nullptr);
	/*
	vkDestroyPrivateDataSlot��Ч�÷�:
	1.�������ʱ�ṩ��VkAllocationCallbacks������������ṩ��֮���ݵ�callbacks
	2.�������ʱû���ṩVkAllocationCallbacks��������pAllocator���봫��NULL
	
	*/




}

void DefferedHostOperationPrivateDataAndAccelarationStructureTest::AccelerationStructureTest()
{
	//Acceleration Structures �μ�p3210
	{
		/*
		Acceleration Structures���ٽṹ��ʵ��������Ч��������ray tracing query���������м���������ݡ���Ӧ���������������䣬���٣�����ִ�к͸��£�ͬ����ray tracing query��ʹ�õ���Դ��

		Acceleration Structures��Ϊ�������ͣ�top level acceleration structures �Լ� bottom level acceleration structures
		

		*/

		//Geometry  ��ָΪ�����λ���������İ�Χ��

		//Top Level Acceleration Structures   ���ж� bottom level acceleration structure�����ã��μ�p3211

		//Bottom Level Acceleration Structures  Ϊһ��geometries������

		//Acceleration Structure Update Rules �μ�3211
		{
			/*
			Acceleration Structure�Ĳ���ͨ�����ַ�ʽ���У�һ����ͨ������������һ����ͨ�����²���

			���²�����һЩ���ƣ��ڴ������ٽṹ��flags���Ƿ���VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT��VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT����VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISPLACEMENT_MICROMAP_UPDATE_NV �в�ͬ��������μ� p3211
			*/
		}


		//Inactive Primitives and Instances  �μ�3212
		{
			/*
			Acceleration structures ����ʹ����������������� inactive primitives ���� instances.
			
			���һ��ͼԪprimitive���κ�һ�������xֵΪNaN,��˵����ͼԪ��inactive�ģ��ڹ������ٽṹʱ��inactive primitives�ᱻ���ԣ���ray tracing query�в��ᱻ���ǡ�

			���һ��instance��acceleration structure����Ϊ0����˵����instance��inactive�ģ��ڹ������ٽṹʱ��inactive instances�ᱻ���ԣ���ray tracing query�в��ᱻ���ǡ�
			
			�����С��x����ֵΪNaN����˵����AABB��Χ����inactive�ģ��ڹ������ٽṹʱ��inactive AABB��Χ�лᱻ���ԣ���ray tracing query�в��ᱻ���ǡ�
			
			inactive��primitives��instances���� InstanceId �Լ� PrimitiveId���Զ�����
			*/

		}


		//Building Acceleration Structures  �μ�3213
		{
			VkAccelerationStructureNV srcAccelerationStructureNV{};
			VkAccelerationStructureNV dstAccelerationStructureNV{};
			VkAccelerationStructureKHR srcAccelerationStructureKHR{};
			VkAccelerationStructureKHR dstAccelerationStructureKHR{};
			VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

			//���ܼ��ٽṹ
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
						trianglesNV.vertexData = VkBuffer{/*��������һ����Ч��VkBuffer*/ };
						trianglesNV.vertexOffset = 0;
						trianglesNV.vertexStride = 12;
						trianglesNV.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
						trianglesNV.vertexCount = 3;
						trianglesNV.indexData = VkBuffer{/*��������һ����Ч��VkBuffer*/ };
						trianglesNV.indexOffset = 0;
						trianglesNV.indexType = VK_INDEX_TYPE_UINT16;
						trianglesNV.indexCount = 3;
						trianglesNV.transformData = VkBuffer{/*��������һ����Ч��VkBuffer*/ };
						trianglesNV.transformOffset = 0;
					}
					geometryDataNV.triangles = trianglesNV;
					VkGeometryAABBNV aabbs{};
					{
						aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
						aabbs.pNext = nullptr;
						aabbs.aabbData = VkBuffer{/*��������һ����Ч��VkBuffer*/ };
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
				VkBuffer{/*��������һ����Ч��VkBuffer*/ }/* instanceData������һ�鶨����ٽṹ��VkAccelerationStructureInstanceKHR�����Ϊbottom level acceleration structures�����ΪNULL */, 0/*instanceOffset,Ϊ instanceData�в�������ʼ�ֽ�ƫ��*/,
				VK_TRUE/*update,ָ���Ƿ�ʹ��src�е����ݸ���dst�� acceleration structure������.*/, dstAccelerationStructureNV/*dst, ָ��Ҫ������acceleration structure*/, srcAccelerationStructureNV/* src��Ϊ�Ѿ����ڵ����ڸ���dst��acceleration structure*/, 
				VkBuffer{/*��������һ����Ч��VkBuffer*/ }/*scratch��Ϊ��������acceleration structure�� scratch memory��VkBuffer .*/, 0/*scratchOffset,Ϊ scratch�е���ʼ�ֽ�ƫ����*/);//��src��dst �Լ�scratch�ı�����VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage����ͬ������VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR ���� VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR���з���
			/*
			vkCmdBuildAccelerationStructureNV��Ч�÷�:
			1.geometryCount ����С�ڵ���VkPhysicalDeviceRayTracingPropertiesNV::maxGeometryCount
			2.*dst �����Լ��ݵ�VkAccelerationStructureInfoNV��������VkAccelerationStructureInfoNV::type��VkAccelerationStructureInfoNV::flags��ͬ��dst�� VkAccelerationStructureInfoNV::instanceCount�Լ�VkAccelerationStructureInfoNV::geometryCount���ڵ��ڹ�����С����dst��VkAccelerationStructureInfoNV::pGeometries ��ÿ��Ԫ�صĹ�����С����Ҫ���ڵ���vertices, indices, �Լ� AABBs��������
			3.���update ΪVK_TRUE,��src ����ΪVK_NULL_HANDLE���ұ�������ǰ��VkAccelerationStructureInfoNV::flags������VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV ����
			4.���update ΪVK_FALSE����1������vkGetAccelerationStructureMemoryRequirementsNV����VkAccelerationStructureMemoryRequirementsInfoNV::accelerationStructureΪdst�Լ�VkAccelerationStructureMemoryRequirementsInfoNV::type����ΪVK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV�Ĳ������ص�VkMemoryRequirements�е�size ����С�ڵ���scratch VkBuffer�Ĵ�С��ȥscratchOffset
									   ��2������vkGetAccelerationStructureMemoryRequirementsNV����VkAccelerationStructureMemoryRequirementsInfoNV::accelerationStructureΪdst�Լ�VkAccelerationStructureMemoryRequirementsInfoNV::type����ΪVK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV�Ĳ������ص�VkMemoryRequirements�е�size ����С�ڵ���scratch VkBuffer�Ĵ�С��ȥscratchOffset
			5.scratch ������VK_BUFFER_USAGE_RAY_TRACING_BIT_NV ����
			6.���instanceData ��ΪVK_NULL_HANDLE��instanceData������VK_BUFFER_USAGE_RAY_TRACING_BIT_NV ����
			7.instanceData�а�����ÿ��VkAccelerationStructureInstanceKHR::accelerationStructureReference��ֵ��������˴�vkGetAccelerationStructureHandleNV��ȡ��ֵһ����Ч���豸��ַ
			8.���update ΪVK_TRUE����1����ǰ��active��object ���ܱ�Ϊinactive�ģ���Inactive Primitives and Instances p3212
									  ��2����ǰ��inactive��object ���ܱ�Ϊactive�ģ���Inactive Primitives and Instances p3212
			9.���update ΪVK_FALSE����src�Լ�dst�������ͬһ��������߲������κ�memory aliasing
			10.dst ����ͨ��vkBindAccelerationStructureMemoryNV�Ѿ��󶨵������������ĵ�����VkDeviceMemory��������
			
			*/



			//����acceleration structures KHR
			VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{};//������Ϣ��p3235
			accelerationStructureBuildGeometryInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
			accelerationStructureBuildGeometryInfoKHR.pNext = nullptr;
			accelerationStructureBuildGeometryInfoKHR.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR;//VkBuildAccelerationStructureFlagBitsKHR ���ֵλ����ָ������Ĳ���
			accelerationStructureBuildGeometryInfoKHR.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;//ΪVkAccelerationStructureTypeKHR ֵָ�����ٽṹ����������
			accelerationStructureBuildGeometryInfoKHR.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;// VkBuildAccelerationStructureModeKHR ֵָ������������
			/*
			VkBuildAccelerationStructureModeKHR:
			VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR:  ָ����ʹ��ָ���ļ����幹��dstAccelerationStructure
			VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR:  ָ����ʹ��srcAccelerationStructure�е����ݹ���dstAccelerationStructure��Ȼ�����ָ���ļ�����
			*/
			accelerationStructureBuildGeometryInfoKHR.srcAccelerationStructure = srcAccelerationStructureKHR;//Ϊ��mode ΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR��ʱ����������dstAccelerationStructure ��һ���ִ�� acceleration structure
			accelerationStructureBuildGeometryInfoKHR.dstAccelerationStructure = dstAccelerationStructureKHR;//ΪҪ���µ�acceleration structure
			accelerationStructureBuildGeometryInfoKHR.geometryCount = 1;//ָ��Ҫ������dstAccelerationStructure �еļ���������
			VkAccelerationStructureGeometryKHR geometryKHR{};
			{
				geometryKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;;
				geometryKHR.pNext = nullptr;
				geometryKHR.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;//VkGeometryFlagBitsKHR ���ֵλ����ָ��geometry��ι����Ķ�����Ϣ
				geometryKHR.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;//�����˸ü��ٽṹ���õ�����
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
								accelerationStructureTrianglesDisplacementMicromapNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
								accelerationStructureTrianglesDisplacementMicromapNV.pNext = nullptr;
								accelerationStructureTrianglesOpacityMicromapEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
								accelerationStructureTrianglesOpacityMicromapEXT.pNext = nullptr;
							}
						
						};




						trianglesKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
						AccelerationStructureGeometryTrianglesDataKHREXT accelerationStructureGeometryTrianglesDataKHREXT{};
						//VkAccelerationStructureGeometryTrianglesDataKHR.pNext
						{
							//VkAccelerationStructureGeometryMotionTrianglesDataNV��  �����ýṹ��ָ����time 1.0ʱ�ļ�����λ�ã�VkAccelerationStructureGeometryTrianglesDataKHRָ��Ϊtime 0.0��λ�ã��м��timeͨ�����Բ�ֵ����
							VkAccelerationStructureGeometryMotionTrianglesDataNV& accelerationStructureGeometryMotionTrianglesDataNV = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureGeometryMotionTrianglesDataNV;
							accelerationStructureGeometryMotionTrianglesDataNV.vertexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ������geometry��time 1.0ʱ�Ķ������ݵ�device ����host�˵ĵ�ַ


							/*VkAccelerationStructureTrianglesOpacityMicromapEXT��  �����ýṹ��ָ����geometry����micromap
							
							�Լ������е�ÿ�������Σ���ʹ��indexBuffer, indexType �Լ� indexStride���������������һ������ֵ��һ��  VkOpacityMicromapSpecialIndexEXT���޷���ת���õ�����������ε���Ϊ�ο�Ray Opacity Micromap.p3333 ,����ʹ��micromap��������ֵ���� baseTriangle�� opacity micromap information
							
							VkOpacityMicromapSpecialIndexEXT:
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_TRANSPARENT_EXT:  ָ��������������ȫ͸��
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_OPAQUE_EXT:  ָ��������������ȫ��͸��
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_TRANSPARENT_EXT:  ָ�����������ε�͸����δ֪
							VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_OPAQUE_EXT:  ָ�����������εĲ�͸����δ֪
							*/
							VkAccelerationStructureTrianglesOpacityMicromapEXT& accelerationStructureTrianglesOpacityMicromapEXT = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureTrianglesOpacityMicromapEXT;
							accelerationStructureTrianglesOpacityMicromapEXT.baseTriangle = 0;//Ϊ��ӵ��Ǹ������������ϵ�һ��ֵ
							accelerationStructureTrianglesOpacityMicromapEXT.indexBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����triangle ���������ݵ�device ����host�˵ĵ�ַ
							accelerationStructureTrianglesOpacityMicromapEXT.indexStride = 32;//Ϊ������������������֮���ֱ�Ӳ���
							accelerationStructureTrianglesOpacityMicromapEXT.indexType = VK_INDEX_TYPE_UINT32;//Ϊ����micromap �������ζ�����������
							accelerationStructureTrianglesOpacityMicromapEXT.micromap = VkMicromapEXT{ /*��������һ����Ч��VkMicromapEXT*/ };//Ϊ�����ڸ�geometry�ڵ�micromap����ľ��
							accelerationStructureTrianglesOpacityMicromapEXT.usageCountsCount = 1;//ָ��usage count�ṹ����������������� micromap�Ĵ�С
							VkMicromapUsageEXT usageCount{};
							{
								usageCount.count = 1;
								usageCount.format = VK_FORMAT_R8_UNORM;
								usageCount.subdivisionLevel = 0;
							}
							accelerationStructureTrianglesOpacityMicromapEXT.pUsageCounts = &usageCount;//һ��VkMicromapUsageEXT ����ָ��
							accelerationStructureTrianglesOpacityMicromapEXT.ppUsageCounts = VK_NULL_HANDLE;//һ��ָ��VkMicromapUsageEXT ����ָ�������ָ��
							/*
							VkAccelerationStructureTrianglesOpacityMicromapEXT��Ч�÷�:
							1.pUsageCounts ��ppUsageCounts��ֻ��һ����Ч������һ������ΪVK_NULL_HANDLE
							*/


							/*VkAccelerationStructureTrianglesDisplacementMicromapNV��  �����ýṹ��ָ����geometry����micromap

							�Լ������е�ÿ�������Σ���ʹ��indexBuffer, indexType �Լ� indexStride��������ʹ��micromap��������ֵ���� baseTriangle�� displacement micromap information
							*/
							VkAccelerationStructureTrianglesDisplacementMicromapNV& accelerationStructureTrianglesDisplacementMicromapNV = accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureTrianglesDisplacementMicromapNV;
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleFormat = VK_FORMAT_R32G32B32_SFLOAT;//ָ��displacement  micromap�� bias �� scale �ĸ�ʽ
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorFormat = VK_FORMAT_R32G32B32_SFLOAT;//ָ��displacement  micromap�� displacement vector �ĸ�ʽ
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����displacement  micromap�� bias �� scale ��device ����host�˵ĵ�ַ
							accelerationStructureTrianglesDisplacementMicromapNV.displacementBiasAndScaleStride = 4;//Ϊbias �� scale ֮����ֽڲ���
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����displacement  micromap�� displacement vector ��device ����host�˵ĵ�ַ
							accelerationStructureTrianglesDisplacementMicromapNV.displacementVectorStride = 4;//Ϊ���� displacement vector ֵ֮����ֽڲ���
							accelerationStructureTrianglesDisplacementMicromapNV.displacedMicromapPrimitiveFlags = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����primitive flags ��device ����host�˵ĵ�ַ
							accelerationStructureTrianglesDisplacementMicromapNV.displacedMicromapPrimitiveFlagsStride = 4;//Ϊ���� primitive flags ֵ֮����ֽڲ���
							accelerationStructureTrianglesDisplacementMicromapNV.indexType = VK_INDEX_TYPE_UINT32;//Ϊ����micromap �������ζ�����������
							accelerationStructureTrianglesDisplacementMicromapNV.indexBuffer = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����triangle ���������ݵ�device ����host�˵ĵ�ַ
							accelerationStructureTrianglesDisplacementMicromapNV.indexStride = 32;//Ϊ������������������֮���ֱ�Ӳ���
							accelerationStructureTrianglesDisplacementMicromapNV.baseTriangle = 0;//Ϊ��ӵ��Ǹ������������ϵ�һ��ֵ
							accelerationStructureTrianglesDisplacementMicromapNV.usageCountsCount = 1;//ֵ��usage count�ṹ����������������� micromap�Ĵ�С
							accelerationStructureTrianglesDisplacementMicromapNV.pUsageCounts = &usageCount;//һ��VkMicromapUsageEXT ����ָ��
							accelerationStructureTrianglesDisplacementMicromapNV.ppUsageCounts = VK_NULL_HANDLE;//һ��ָ��VkMicromapUsageEXT ����ָ�������ָ��
							accelerationStructureTrianglesDisplacementMicromapNV.micromap = VkMicromapEXT{ /*��������һ����Ч��VkMicromapEXT*/ };//Ϊ�����ڸ�geometry�ڵ�micromap����ľ��
							/*
							VkAccelerationStructureTrianglesDisplacementMicromapNV��Ч�÷�:
							1.displacementBiasAndScaleFormat �Լ� displacementVectorFormat����ΪVK_FORMAT_UNDEFINED
							2.pUsageCounts ��ppUsageCounts��ֻ��һ����Ч������һ������ΪVK_NULL_HANDLE
							*/
						}
						trianglesKHR.pNext = &accelerationStructureGeometryTrianglesDataKHREXT.accelerationStructureGeometryMotionTrianglesDataNV;
						trianglesKHR.vertexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host ��const��ַ*/  /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ�����������ݵ�device ����host�˵ĵ�ַ
						trianglesKHR.vertexStride = 12;//Ϊÿ���������ֽڲ�����С
						trianglesKHR.maxVertex = 3;//ΪvertexData �еĶ���������ȥ1
						trianglesKHR.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;//Ϊ����Ԫ�ص�����VkFormat��ʽ
						trianglesKHR.indexData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ�����������ݵ�device ����host�˵ĵ�ַ
						trianglesKHR.indexType = VK_INDEX_TYPE_UINT16;//Ϊ����Ԫ�ص��������� VkIndexType
						//VkTransformMatrixKHR   �ȼ���VkTransformMatrixNV
						{
							VkTransformMatrixKHR  transformMatrixKHR{};
							transformMatrixKHR.matrix;//Ϊ3 �� 4 �����ȵķ������ǰ3�б��붨��һ������ľ���
							for (uint32_t i = 0; i < 3; i++)
							{
								for (uint32_t j = 0; j < 4; j++)
								{
									transformMatrixKHR.matrix[i][j] = 0;
								}
							}
							
						}
						trianglesKHR.transformData = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ������ѡ��VkTransformMatrixKHR ���ݵ�device ����host�˵ĵ�ַ��������geometry�Ķ������ڵĿռ䵽���ٽṹ�������ڵĿռ�ı任
						/*
						VkAccelerationStructureGeometryTrianglesDataKHR��Ч�÷�:
						1.vertexStride ������vertexFormat ����С�������ֽڲ�����������
						2.vertexStride ����С�ڵ���pow(2,32) -1
						3.vertexFormat��format features �������VK_FORMAT_FEATURE_ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR
						4.indexType ������ VK_INDEX_TYPE_UINT16, VK_INDEX_TYPE_UINT32 ���� VK_INDEX_TYPE_NONE_KHR
						*/
					}
					geometryDataKHR.triangles = trianglesKHR;// VkAccelerationStructureGeometryTrianglesDataKHR ֵ 
					VkAccelerationStructureGeometryAabbsDataKHR aabbsKHR{};
					{
						aabbsKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
						aabbsKHR.pNext = nullptr;
						// VkAabbPositionsKHR  ��ͬ��VkAabbPositionsNV
						{
							VkAabbPositionsKHR aabbPositionsKHR{};
							aabbPositionsKHR.minX = 0;//Ϊ��Χ��һ���Խǵ�x����
							aabbPositionsKHR.minY = 0;//Ϊ��Χ��һ���Խǵ�y����
							aabbPositionsKHR.minZ = 0;//Ϊ��Χ��һ���Խǵ�z����
							aabbPositionsKHR.maxX = 1;//Ϊ��Χ����һ���Խǵ�x����,�������minX
							aabbPositionsKHR.maxY = 1;//Ϊ��Χ����һ���Խǵ�y����,�������minY
							aabbPositionsKHR.maxZ = 1;//Ϊ��Χ����һ���Խǵ�z����,�������minZ


						}
						aabbsKHR.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����geometry��ÿ������߽��λ������ VkAabbPositionsKHR ��device ����host�˵ĵ�ַ
						aabbsKHR.stride = 64;//Ϊdata������Ԫ��֮����ֽڲ���������Ϊ8�ı������ұ���С�ڵ���pow(2,32)-1
					}
					geometryDataKHR.aabbs = aabbsKHR;// VkAccelerationStructureGeometryAabbsDataKHR ֵ 
					VkAccelerationStructureGeometryInstancesDataKHR instanceDataKHR{};
					{
						instanceDataKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
						instanceDataKHR.pNext = nullptr;
						{
							/*
							Acceleration structure instances���Թ���Ϊһ��top-level acceleration structures.ÿ��instance��top-level acceleration structures�з������֣�����һ�� bottom-level acceleration structure���ڱ任λ�ô�������geometry�����instance����ָ��ͬһ��bottom-level acceleration structure
							*/

							VkAccelerationStructureInstanceKHR accelerationStructureInstanceKHR{}; //��ͬ��VkAccelerationStructureInstanceNV
							accelerationStructureInstanceKHR.accelerationStructureReference = 0;//ΪvkGetAccelerationStructureDeviceAddressKHR ���� vkGetAccelerationStructureHandleNV���ص��豸��ַ ����һ�� VkAccelerationStructureKHR���
							accelerationStructureInstanceKHR.instanceCustomIndex = 0;//Ϊ�û��Զ����24bit����������24bit��������ray shader��ͨ��InstanceCustomIndexKHR����
							accelerationStructureInstanceKHR.mask = 0xFF;//Ϊ��geometry��8bit�Ŀ������루��8bit����ֻ����Cull Mask & instance.mask != 0����¸�instance�Żᱻ����
							accelerationStructureInstanceKHR.instanceShaderBindingTableRecordOffset = 0;//Ϊ24bit����24bit�������ڼ���hit shader�󶨱��������ƫ��ֵ
							accelerationStructureInstanceKHR.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;//ΪӦ�õ���instance��8bit����8bit���� VkGeometryInstanceFlagBitsKHR���ֵ����
							/*
							VkGeometryInstanceFlagBitsKHR���ȼ���VkGeometryInstanceFlagBitsNV��:
							VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR: �Ը�instance�ر�face culling
							VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR: ָ����ת��instance��geometry�е���ľ�����ӣ���Ϊfacing������ռ��ж��壬instance transform����ı�����ķ��򣬵�geometry transform�ᡣ
							VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR:  �Ը�instanceǿ��ʹ����geometry��opaque flag ��λ������������VK_GEOMETRY_OPAQUE_BIT_KHRһ����������Ϊ����ͨ��SPIR-V NoOpaqueKHR ray flag��д��
							VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR:  �Ը�instanceǿ��ʹ����geometry��opaque flag ����λ������û������VK_GEOMETRY_OPAQUE_BIT_KHRһ����������Ϊ����ͨ��SPIR-V OpaqueKHR ray flag��д��
							*/
							accelerationStructureInstanceKHR.transform = VkTransformMatrixKHR{/*��������һ����Ч��VkTransformMatrixKHR*/ };//ΪӦ�õ����ٽṹ�ı任����

							/*
							Acceleration structure  motion instances���Թ���Ϊһ��top-level acceleration structures.ÿ��instance��top-level acceleration structures�з������֣�����һ�� bottom-level acceleration structure���ڰ��� �˶������Լ����� instance��ʱ���ϵ��˶��Ĳ����ı任λ�ô�������geometry
							*/

							VkAccelerationStructureMotionInstanceNV accelerationStructureMotionInstanceNV{};
							accelerationStructureMotionInstanceNV.type = VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV;//Ϊ VkAccelerationStructureMotionInstanceTypeNVֵ�����motion instance�����ͣ�ָ��union���ĸ�������Ч
							/*
							VkAccelerationStructureMotionInstanceTypeNV:
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_STATIC_NV: ָ�����instance�Ǿ�̬��û���κ�instance�ƶ�
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MATRIX_MOTION_NV: ָ�����instance��һ��motion instance�����ƶ�ͨ�����������Ĳ�ֵָ��
							VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV:  ָ�����instance��һ��motion instance�����ƶ�ͨ��SRT decomposition�Ĳ�ֵָ��
							*/
							accelerationStructureMotionInstanceNV.flags = 0;//��ǰδʹ�ã�������Ҫ����֤data�е���Ȼ�ڴ��Ų�����
							VkAccelerationStructureMotionInstanceDataNV accelerationStructureMotionInstanceDataNV{};//����һ��union
							{
								accelerationStructureMotionInstanceDataNV.staticInstance = accelerationStructureInstanceKHR;//����static instance���ݵ�VkAccelerationStructureInstanceKHR
								VkAccelerationStructureMatrixMotionInstanceNV accelerationStructureMatrixMotionInstanceNV{};
								{
									/*
									time 0��time 1֮��ı任Ϊ: transformT0 �� (1 - time) + transformT1 �� time
									*/
									accelerationStructureMatrixMotionInstanceNV.accelerationStructureReference = 0;//ΪvkGetAccelerationStructureDeviceAddressKHR ���� vkGetAccelerationStructureHandleNV���ص��豸��ַ ����һ�� VkAccelerationStructureKHR���
									accelerationStructureMatrixMotionInstanceNV.flags = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR;//ΪӦ�õ���instance��8bit����8bit���� VkGeometryInstanceFlagBitsKHR���ֵ����
									accelerationStructureMatrixMotionInstanceNV.instanceCustomIndex = 0;//Ϊ�û��Զ����24bit����������24bit��������ray shader��ͨ��InstanceCustomIndexKHR����
									accelerationStructureMatrixMotionInstanceNV.mask = 0xFF;// Ϊ��geometry��8bit�Ŀ������루��8bit����ֻ����Cull Mask & instance.mask != 0����¸�instance�Żᱻ����
									accelerationStructureMatrixMotionInstanceNV.instanceShaderBindingTableRecordOffset = 0;//Ϊ24bit����24bit�������ڼ���hit shader�󶨱��������ƫ��ֵ
									accelerationStructureMatrixMotionInstanceNV.transformT0 = VkTransformMatrixKHR{/*��������һ����Ч��VkTransformMatrixKHR*/ };//Ϊһ������Ӧ�õ����ٽṹ��time 0.0�ı任�� VkTransformMatrixKHR
									accelerationStructureMatrixMotionInstanceNV.transformT1 = VkTransformMatrixKHR{/*��������һ����Ч��VkTransformMatrixKHR*/ };//Ϊһ������Ӧ�õ����ٽṹ��time 1.0�ı任�� VkTransformMatrixKHR
								}
								accelerationStructureMotionInstanceDataNV.matrixMotionInstance = accelerationStructureMatrixMotionInstanceNV;//����matrix motion instance���ݵ�VkAccelerationStructureMatrixMotionInstanceNV
								VkAccelerationStructureSRTMotionInstanceNV accelerationStructureSRTMotionInstanceNV{};
								{
									/*
									time 0��time 1֮��ı任Ϊ: transformT0 �� (1 - time) + transformT1 �� time
									*/
									accelerationStructureSRTMotionInstanceNV.accelerationStructureReference = 0;//ΪvkGetAccelerationStructureDeviceAddressKHR ���� vkGetAccelerationStructureHandleNV���ص��豸��ַ ����һ�� VkAccelerationStructureKHR���
									accelerationStructureSRTMotionInstanceNV.flags = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR;//ΪӦ�õ���instance��8bit����8bit���� VkGeometryInstanceFlagBitsKHR���ֵ����
									accelerationStructureSRTMotionInstanceNV.instanceCustomIndex = 0;//Ϊ�û��Զ����24bit����������24bit��������ray shader��ͨ��InstanceCustomIndexKHR����
									accelerationStructureSRTMotionInstanceNV.mask = 0xFF;//Ϊ��geometry��8bit�Ŀ������루��8bit����ֻ����Cull Mask & instance.mask != 0����¸�instance�Żᱻ����
									accelerationStructureSRTMotionInstanceNV.instanceShaderBindingTableRecordOffset = 0;//Ϊ24bit����24bit�������ڼ���hit shader�󶨱��������ƫ��ֵ
									VkSRTDataNV  SRTDataNV{};
									{
										/*
										VkSRTDataNV �����һ������Ԫ��:
										S =    sx   a   b   pvx
											   0    sy  c   pvy
											   0    0   sz  pvz
										
										VkSRTDataNV ����ڶ�����Ԫ��Ԫ��:
										R =    qx   qy   qz   qw	  ���ж���Ϊ�ƹ�һ������[ax,ay,zx] ��תtheta�Ƕȣ��� [ qx, qy, qz ] = sin(theta/2) �� [ ax, ay, az ] ��qw = cos(theta/2)

										VkSRTDataNV ���������λ�ƾ���Ԫ��
										T =   1     0    0   tx
											  0     1    0   ty
											  0     0    1   tz

										VkSRTDataNV��������ձ任Ϊ:  T �� R �� S 
										*/
										SRTDataNV.sx = 0;//Ϊ�任��xά�ϵ�������
										SRTDataNV.a = 0;//Ϊ�б�任��һ������
										SRTDataNV.b = 0;//Ϊ�б�任��һ������
										SRTDataNV.pvx = 0;//Ϊ�任֧���x�����ϵ�ֵ
										SRTDataNV.sy = 0;//Ϊ�任��yά�ϵ�������
										SRTDataNV.c = 0;//Ϊ�б�任��һ������
										SRTDataNV.pvy = 0;//Ϊ�任֧���y�����ϵ�ֵ
										SRTDataNV.sz = 0;//Ϊ�任��zά�ϵ�������
										SRTDataNV.pvz = 0;//Ϊ�任֧���z�����ϵ�ֵ
										SRTDataNV.qx = 0;//Ϊ��Ԫ����ת��x����ֵ
										SRTDataNV.qy = 0;//Ϊ��Ԫ����ת��y����ֵ
										SRTDataNV.qz = 0;//Ϊ��Ԫ����ת��z����ֵ
										SRTDataNV.qw = 0;//Ϊ��Ԫ����ת��w����ֵ
										SRTDataNV.tx = 0;//Ϊ��ת��ƽ�Ƶ�x����ֵ
										SRTDataNV.ty = 0;//Ϊ��ת��ƽ�Ƶ�y����ֵ
										SRTDataNV.tz = 0;//Ϊ��ת��ƽ�Ƶ�z����ֵ

									}
									accelerationStructureSRTMotionInstanceNV.transformT0 = SRTDataNV;//Ϊһ������Ӧ�õ����ٽṹ��time 0.0�ı任�� VkSRTDataNV
									accelerationStructureSRTMotionInstanceNV.transformT1 = SRTDataNV;//Ϊһ������Ӧ�õ����ٽṹ��time 1.0�ı任�� VkSRTDataNV
								}
								accelerationStructureMotionInstanceDataNV.srtMotionInstance = accelerationStructureSRTMotionInstanceNV;//Ϊ���� SRT motion instance���ݵ� VkAccelerationStructureSRTMotionInstanceNV
							}

							accelerationStructureMotionInstanceNV.data = accelerationStructureMotionInstanceDataNV;//��һ��VkAccelerationStructureMotionInstanceDataNV ������motion instance������


						}
						instanceDataKHR.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host��const��ַ*//*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//���arrayOfPointers ΪVK_TRUE����dataָ��һ�����飬������ÿ��Ԫ����һ��ָ��VkAccelerationStructureInstanceKHR �ṹ���ָ�룬����dataָ��һ��VkAccelerationStructureInstanceKHR ���� VkAccelerationStructureMotionInstanceNV �ṹ�������
						instanceDataKHR.arrayOfPointers = VK_FALSE;//ָ��data�Ƿ�������һ���ַ����ֵ���߾���һ������
					}
					geometryDataKHR.instances = instanceDataKHR;// VkAccelerationStructureGeometryInstancesDataKHR ֵ 
				}
				geometryKHR.geometry = geometryDataKHR;// VkAccelerationStructureGeometryDataKHR��unionֵ�����ü��ٽṹ���õļ�������
			}
			accelerationStructureBuildGeometryInfoKHR.pGeometries = &geometryKHR;//һ��VkAccelerationStructureGeometryKHR ����ָ��
			accelerationStructureBuildGeometryInfoKHR.ppGeometries = VK_NULL_HANDLE;//һ��VkAccelerationStructureGeometryKHR ����ָ�������ָ��  ,��pGeometries ����ͬʱʹ��,����һ��ΪVK_NULL_HANDLE,shader���� RayGeometryIndexKHR���з���
			accelerationStructureBuildGeometryInfoKHR.scratchData = VkDeviceOrHostAddressKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressKHR*/ };//Ϊ���ڹ�����scratch�� device ���� host�˵��ڴ��ַ
			/*
			VkAccelerationStructureBuildGeometryInfoKHR��Ч�÷�:
			1.type ����ΪVK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
			2.���geometryCount ��Ϊ0����pGeometries ��ppGeometries ������һ��Ϊ��Ч��ָ�룬����һ��ΪNULL
			3.���type ΪVK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR����1��pGeometries ���� ppGeometries �е�geometryType ����ΪVK_GEOMETRY_TYPE_INSTANCES_KHR
																		 ��2��geometryCount ����Ϊ1
			4.���type ΪVK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR����1��pGeometries ���� ppGeometries �е�geometryType ����ΪVK_GEOMETRY_TYPE_INSTANCES_KHR
																		    ��2��pGeometries ���� ppGeometries �е�����geometry��geometryType������ͬ
																		    ��3��geometryCount ����С�ڵ���VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxGeometryCount
																		    ��4�����pGeometries ���� ppGeometries �е�����geometry��geometryTypeΪVK_GEOMETRY_TYPE_AABBS_KHR��������geometry�е�AABBs ����С��VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPrimitiveCount
																		    ��5�����pGeometries ���� ppGeometries �е�����geometry��geometryTypeΪVK_GEOMETRY_TYPE_TRIANGLES_KHR��������geometry�е�triangles ����С��VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPrimitiveCount
			5.���flags��VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR����flags���ܺ�VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR
			6.���dstAccelerationStructure ��VkAccelerationStructureCreateInfoKHR::flags�к�VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV ��������flags�б��뺬��VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV
			7.���flags�б��뺬��VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV����dstAccelerationStructure ��VkAccelerationStructureCreateInfoKHR::flags�к�VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV ����
			8.���flags�к�VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV����type ����ΪVK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
			9.���flags�к�VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT����flags �����ٰ���VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT

			*/



			VkAccelerationStructureBuildRangeInfoKHR accelerationStructureBuildRangeInfoKHR{};
			accelerationStructureBuildRangeInfoKHR.firstVertex = 0;
			accelerationStructureBuildRangeInfoKHR.primitiveCount = 1;
			accelerationStructureBuildRangeInfoKHR.transformOffset = 0;
			accelerationStructureBuildRangeInfoKHR.transformOffset = 0;
			VkAccelerationStructureBuildRangeInfoKHR* accelerationStructureBuildRangeInfoKHRPointer = &accelerationStructureBuildRangeInfoKHR;

			vkCmdBuildAccelerationStructuresKHR(commandBuffer, 1/*infoCount,ָ��Ҫ�����ļ��ٽṹ������*/, &accelerationStructureBuildGeometryInfoKHR/*pInfos,infoCount��VkAccelerationStructureBuildGeometryInfoKHR ����ָ��ָ����ز��� */, &accelerationStructureBuildRangeInfoKHRPointer/*ppBuildRangeInfos��infoCount��VkAccelerationStructureBuildRangeInfoKHRָ���������ָ��ָ��pInfo�м��ٽṹ���ݴ洢�Ķ�̬ƫ��*/);//��srcAccelerationStructure��dstAccelerationStructure �Լ�scratchData�ı�����VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage����ͬ������VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR ���� VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR���з���,����֮�����е�bufferֻ������ͬ�׶���VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR���ʣ�
			/*
			vkCmdBuildAccelerationStructuresKHR��Ч�÷�:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure���Ա��뿪��
			2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildAccelerationStructureModeKHRֵ
			3.pInfos���κ�srcAccelerationStructure����VK_NULL_HANDLE��Ԫ�أ���srcAccelerationStructure������һ����Ч��VkAccelerationStructureKHR ���
			4.��pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR�����Ԫ�ص�srcAccelerationStructure����ΪVK_NULL_HANDLE	
			5.��pInfos���κ�Ԫ�ص�srcAccelerationStructure ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure ��ͬ
			6.pInfos���κ�Ԫ�ص�dstAccelerationStructure ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure ��ͬ
			7.pInfos���κ�Ԫ�ص�dstAccelerationStructure ������һ����Ч��VkAccelerationStructureKHR ���
			8.pInfos��ÿ��Ԫ�أ���1�������typeΪVK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR������dstAccelerationStructure����VkAccelerationStructureCreateInfoKHR::typeΪVK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ���� VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR����
								  ��2�������typeΪVK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR������dstAccelerationStructure����VkAccelerationStructureCreateInfoKHR::typeΪVK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR ���� VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR����
								  ��3�������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����srcAccelerationStructure��inactive primitives���ܱ�Ϊactive�ģ�active primitives���ܱ�Ϊinactive��
			9.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ܱ��κ�����Ԫ�ص�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��  pGeometries���� ppGeometries�е�Ԫ�ص� geometry.instances.data����
			10.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR  ��Ԫ�ص�srcAccelerationStructure���ڴ淶Χ�ص�
			11.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure���ڴ淶Χ�ص�
			12.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�scratchData���ڴ淶Χ�ص�
			13.pInfos���κ�Ԫ�ص�scratchData���ڴ淶Χ���ܺ��κ�����Ԫ�ص�scratchData���ڴ淶Χ�ص�
			14.pInfos���κ�Ԫ�ص�scratchData���ڴ淶Χ���ܺ��κ�����modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR(������ͬԪ��)  ��Ԫ�ص�srcAccelerationStructureԪ�ص�srcAccelerationStructure���ڴ淶Χ�ص�
			15.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��  pGeometries���� ppGeometries�е��κ�Ԫ�ص� geometry.instances.data���õļ��ٽṹ���ڴ淶Χ�ص�
			16.pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����1����srcAccelerationStructure��������ǰ��VkAccelerationStructureBuildGeometryInfoKHR::flags������VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR ��������
																							  ��2������srcAccelerationStructure ��dstAccelerationStructure ������ͬһ��������߲������κ�memory aliasing
																							  ��3������geometryCount �����srcAccelerationStructure���һ�ι�����geometryCount��ͬ
																							  ��4������flags �����srcAccelerationStructure���һ�ι�����flags��ͬ
																							  ��5������type �����srcAccelerationStructure���һ�ι�����type��ͬ
																							  ��6����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�� ����geometryType �����srcAccelerationStructure���һ�ι�����geometryType��ͬ
																							  ��7����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�� ����flags �����srcAccelerationStructure���һ�ι�����flags��ͬ
																							  ��8����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.vertexFormat �����srcAccelerationStructure���һ�ι�����geometry.triangles.vertexFormat��ͬ
																							  ��9����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.maxVertex �����srcAccelerationStructure���һ�ι�����geometry.triangles.maxVertex��ͬ
																							  ��10����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.indexType �����srcAccelerationStructure���һ�ι�����geometry.triangles.indexType��ͬ
																							  ��11����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�����srcAccelerationStructure���һ�ι�����geometry.triangles.transformDataΪNULL����geometry.triangles.transformData ����ΪNULL 
																							  ��12����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�����srcAccelerationStructure���һ�ι�����geometry.triangles.transformData��ΪNULL����geometry.triangles.transformData ���벻ΪNULL 
																							  ��13����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�������geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����ÿ�����õ�����ֵ�����srcAccelerationStructure���һ�ι������õ�����ֵ��ͬ
																							  ��14����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�������Ӧ��VkAccelerationStructureBuildRangeInfoKHR��primitiveCount �����srcAccelerationStructure���һ�ι�����primitiveCount��ͬ
																							  ��15����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�������geometryʹ������indices�������Ӧ��VkAccelerationStructureBuildRangeInfoKHR��firstVertex �����srcAccelerationStructure���һ�ι�����firstVertex ��ͬ
			17.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries ÿ����geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��Ԫ�أ����Ӧ��ppBuildRangeInfos[i][j].primitiveCount ����С�ڵ���VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount
			18.��pInfos�е�ÿ��Ԫ�أ����ڴ���dstAccelerationStructure��buffer����󶨵�VkDeviceMemory������
			19.pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR�������ڴ���dstAccelerationStructure��buffer����󶨵�VkDeviceMemory������
			20.��pInfos�е�ÿ��Ԫ�أ����ڴ�����pGeometries ���� ppGeometries��geometryType��VK_GEOMETRY_TYPE_INSTANCES_KHR ���õ�acceleration structure��buffer����󶨵�VkDeviceMemory������
			21.���pInfos[i].modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ���� VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����������pInfos[i].scratchData.deviceAddress��pInfos[i].scratchData.deviceAddress + N - 1 ֮��ĵ�ַ��������ͬһ��buffer��device address range�ڣ�����N��vkGetAccelerationStructureBuildSizesKHR������ͬVkAccelerationStructureBuildGeometryInfoKHR�Լ�primitive count  ���ص�VkAccelerationStructureBuildSizesInfoKHR�ṹ��buildScratchSize��Ա��ֵ
			22.�κ���buffer device addresses ��pInfos[i].pGeometries �Լ� pInfos[i].ppGeometries�е�����geometry.triangles.vertexData, geometry.triangles.indexData, geometry.triangles.transformData, geometry.aabbs.data, �Լ� geometry.instances.data��ָ��buffer������VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR ����
			23.�κ���buffer device addresses �� pInfos[i].scratchData.deviceAddress��ָ��buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
			24.��pInfos�е�ÿ��Ԫ�أ���1����scratchData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
									   ��2�����scratchData.deviceAddress��һ��non-sparse��address�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
									   ��3����scratchData.deviceAddress ������VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment�ı���
			25.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_TRIANGLES_KHR ��Ԫ�أ���1��geometry.triangles.vertexData.deviceAddress������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��2�����geometry.triangles.vertexData.deviceAddress����non-sparse ��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��3��geometry.triangles.vertexData.deviceAddress�б�����뵽vertexFormat����С�������ֽ�����С
																															   ��4�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����geometry.triangles.indexData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��5�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR�����geometry.triangles.indexData.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��6�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����geometry.triangles.indexData.deviceAddress �б�����뵽indexType���ֽ�����С
																															   ��7�����geometry.triangles.transformData.deviceAddress ��Ϊ0����geometry.triangles.transformData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��8�����geometry.triangles.transformData.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��9�����geometry.triangles.transformData.deviceAddress ��Ϊ0����geometry.triangles.transformData.deviceAddress �б�����뵽16�ֽڴ�С
			26.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_AABBS_KHR ��Ԫ�أ���1��geometry.aabbs.data.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																														   ��2�����geometry.aabbs.data.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																														   ��3��geometry.aabbs.data.deviceAddress ������뵽8�ֽ�
			27.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR ��Ԫ�أ���1�����geometry.arrayOfPointers ΪVK_FALSE����geometry.instances.data.deviceAddress ������뵽16�ֽ�
																															   ��2�����geometry.arrayOfPointers ΪVK_TRUE����geometry.instances.data.deviceAddress ������뵽8�ֽ�
																															   ��3�����geometry.arrayOfPointers ΪVK_TRUE����geometry.instances.data.deviceAddress�ڴ��е�ÿ��Ԫ�ر�����뵽16�ֽ�
																															   ��4��geometry.instances.data.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��5�����geometry.instances.data.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��6��geometry.instances.data.deviceAddress�ڴ��е�ÿ��VkAccelerationStructureInstanceKHR::accelerationStructureReference ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address ����0
			28.commandBuffer ������һ��protected command buffer
			29.��pInfos[i]��ÿ��Ԫ�أ�dstAccelerationStructure ������VkAccelerationStructureCreateInfoKHR::size���ڵ��ڲ�ѯ���ص��ڴ��С��������vkGetAccelerationStructureBuildSizesKHR������pBuildInfo = pInfos[i]�Լ�pMaxPrimitiveCounts��ÿ��Ԫ��Ҫ���ڵ��ڶ�ӦppBuildRangeInfos[i][j].primitiveCount��ֵ��j��[0,pInfos[i].geometryCount)
			30.ppBuildRangeInfos[i]��ÿ��Ԫ�ر�����һ����Ч��pInfos[i].geometryCount �� VkAccelerationStructureBuildRangeInfoKHR �ṹ��ָ�������ָ��
			*/




			//���� acceleration structures������һЩ������device�л�ȡ
			VkDeviceAddress parameDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };
			uint32_t paramStride{};
			uint32_t maxPrimitiveCount{};
			uint32_t* pMaxPrimitiveCount = &maxPrimitiveCount;
			vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, 1/*infoCount,ָ��Ҫ�����ļ��ٽṹ������*/, &accelerationStructureBuildGeometryInfoKHR/*pInfos,infoCount��VkAccelerationStructureBuildGeometryInfoKHR ����ָ��ָ����ز��� */,
				&parameDeviceAddress/*pIndirectDeviceAddresses,ΪinfoCount�� buffer device addresses��ָ�� pInfos[i].geometryCount VkAccelerationStructureBuildRangeInfoKHRָ�����ٽṹ���ݴ洢�Ķ�̬ƫ��*/, &paramStride/*pIndirectStrides,ΪinfoCount��pIndirectDeviceAddresses��Ԫ��֮����ֽڲ���.*/, &pMaxPrimitiveCount/*ppMaxPrimitiveCounts,ΪinfoCount��ָ��pInfos[i].geometryCount��ֵ��ָ�������ָ��ָ��ÿ��geometry����������ͼԪ����*/);// pIndirectDeviceAddresses��VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR pipeline stage��ͬ������VK_ACCESS_INDIRECT_COMMAND_READ_BIT���з��ʣ���������Դ��ͬ���ͷ��ʺ� vkCmdBuildAccelerationStructuresKHR��ͬ
			/*
			vkCmdBuildAccelerationStructuresIndirectKHR��Ч�÷�:
			1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructureIndirectBuild���Ա��뿪��
			2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildAccelerationStructureModeKHRֵ
			3.pInfos���κ�srcAccelerationStructure����VK_NULL_HANDLE��Ԫ�أ���srcAccelerationStructure������һ����Ч��VkAccelerationStructureKHR ���
			4.��pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR�����Ԫ�ص�srcAccelerationStructure����ΪVK_NULL_HANDLE
			5.��pInfos���κ�Ԫ�ص�srcAccelerationStructure ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure ��ͬ
			6.pInfos���κ�Ԫ�ص�dstAccelerationStructure ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure ��ͬ
			7.pInfos���κ�Ԫ�ص�dstAccelerationStructure ������һ����Ч��VkAccelerationStructureKHR ���
			8.pInfos��ÿ��Ԫ�أ���1�������typeΪVK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR������dstAccelerationStructure����VkAccelerationStructureCreateInfoKHR::typeΪVK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ���� VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR����
								  ��2�������typeΪVK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR������dstAccelerationStructure����VkAccelerationStructureCreateInfoKHR::typeΪVK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR ���� VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR����
								  ��3�������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����srcAccelerationStructure��inactive primitives���ܱ�Ϊactive�ģ�active primitives���ܱ�Ϊinactive��
			9.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ܱ��κ�����Ԫ�ص�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��  pGeometries���� ppGeometries�е�Ԫ�ص� geometry.instances.data����
			10.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR  ��Ԫ�ص�srcAccelerationStructure���ڴ淶Χ�ص�
			11.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�dstAccelerationStructure���ڴ淶Χ�ص�
			12.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�scratchData���ڴ淶Χ�ص�
			13.pInfos���κ�Ԫ�ص�scratchData���ڴ淶Χ���ܺ��κ�����Ԫ�ص�scratchData���ڴ淶Χ�ص�
			14.pInfos���κ�Ԫ�ص�scratchData���ڴ淶Χ���ܺ��κ�����modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR(������ͬԪ��)  ��Ԫ�ص�srcAccelerationStructureԪ�ص�srcAccelerationStructure���ڴ淶Χ�ص�
			15.pInfos���κ�Ԫ�ص�dstAccelerationStructure���ڴ淶Χ���ܺ��κ�����Ԫ�ص�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��  pGeometries���� ppGeometries�е��κ�Ԫ�ص� geometry.instances.data���õļ��ٽṹ���ڴ淶Χ�ص�
			16.pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����1����srcAccelerationStructure��������ǰ��VkAccelerationStructureBuildGeometryInfoKHR::flags������VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR ��������
																							  ��2������srcAccelerationStructure ��dstAccelerationStructure ������ͬһ��������߲������κ�memory aliasing
																							  ��3������geometryCount �����srcAccelerationStructure���һ�ι�����geometryCount��ͬ
																							  ��4������flags �����srcAccelerationStructure���һ�ι�����flags��ͬ
																							  ��5������type �����srcAccelerationStructure���һ�ι�����type��ͬ
																							  ��6����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�� ����geometryType �����srcAccelerationStructure���һ�ι�����geometryType��ͬ
																							  ��7����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�� ����flags �����srcAccelerationStructure���һ�ι�����flags��ͬ
																							  ��8����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.vertexFormat �����srcAccelerationStructure���һ�ι�����geometry.triangles.vertexFormat��ͬ
																							  ��9����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.maxVertex �����srcAccelerationStructure���һ�ι�����geometry.triangles.maxVertex��ͬ
																							  ��10����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR������geometry.triangles.indexType �����srcAccelerationStructure���һ�ι�����geometry.triangles.indexType��ͬ
																							  ��11����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�����srcAccelerationStructure���һ�ι�����geometry.triangles.transformDataΪNULL����geometry.triangles.transformData ����ΪNULL
																							  ��12����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�����srcAccelerationStructure���һ�ι�����geometry.triangles.transformData��ΪNULL����geometry.triangles.transformData ���벻ΪNULL
																							  ��13����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�������geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����ÿ�����õ�����ֵ�����srcAccelerationStructure���һ�ι������õ�����ֵ��ͬ
																							  ��14����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�����geometryType ΪVK_GEOMETRY_TYPE_TRIANGLES_KHR�������Ӧ��VkAccelerationStructureBuildRangeInfoKHR��primitiveCount �����srcAccelerationStructure���һ�ι�����primitiveCount��ͬ
																							  ��15����ÿ������pGeometries ����ppGeometries ���õ�VkAccelerationStructureGeometryKHR�ṹ�������geometryʹ������indices�������Ӧ��VkAccelerationStructureBuildRangeInfoKHR��firstVertex �����srcAccelerationStructure���һ�ι�����firstVertex ��ͬ
			17.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries ÿ����geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR��Ԫ�أ����Ӧ��ppBuildRangeInfos[i][j].primitiveCount ����С�ڵ���VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount
			18.��pInfos�е�ÿ��Ԫ�أ����ڴ���dstAccelerationStructure��buffer����󶨵�VkDeviceMemory������
			19.pInfos��ÿ��Ԫ�أ������modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR�������ڴ���dstAccelerationStructure��buffer����󶨵�VkDeviceMemory������
			20.��pInfos�е�ÿ��Ԫ�أ����ڴ�����pGeometries ���� ppGeometries��geometryType��VK_GEOMETRY_TYPE_INSTANCES_KHR ���õ�acceleration structure��buffer����󶨵�VkDeviceMemory������
			21.���pInfos[i].modeΪVK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ���� VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR����������pInfos[i].scratchData.deviceAddress��pInfos[i].scratchData.deviceAddress + N - 1 ֮��ĵ�ַ��������ͬһ��buffer��device address range�ڣ�����N��vkGetAccelerationStructureBuildSizesKHR������ͬVkAccelerationStructureBuildGeometryInfoKHR�Լ�primitive count  ���ص�VkAccelerationStructureBuildSizesInfoKHR�ṹ��buildScratchSize��Ա��ֵ
			22.�κ���buffer device addresses ��pInfos[i].pGeometries �Լ� pInfos[i].ppGeometries�е�����geometry.triangles.vertexData, geometry.triangles.indexData, geometry.triangles.transformData, geometry.aabbs.data, �Լ� geometry.instances.data��ָ��buffer������VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR ����
			23.�κ���buffer device addresses �� pInfos[i].scratchData.deviceAddress��ָ��buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
			24.��pInfos�е�ÿ��Ԫ�أ���1����scratchData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
									   ��2�����scratchData.deviceAddress��һ��non-sparse��address�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
									   ��3����scratchData.deviceAddress ������VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment�ı���
			25.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_TRIANGLES_KHR ��Ԫ�أ���1��geometry.triangles.vertexData.deviceAddress������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��2�����geometry.triangles.vertexData.deviceAddress����non-sparse ��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��3��geometry.triangles.vertexData.deviceAddress�б�����뵽vertexFormat����С�������ֽ�����С
																															   ��4�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����geometry.triangles.indexData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��5�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR�����geometry.triangles.indexData.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��6�����geometry.triangles.indexType ��ΪVK_INDEX_TYPE_NONE_KHR����geometry.triangles.indexData.deviceAddress �б�����뵽indexType���ֽ�����С
																															   ��7�����geometry.triangles.transformData.deviceAddress ��Ϊ0����geometry.triangles.transformData.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��8�����geometry.triangles.transformData.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��9�����geometry.triangles.transformData.deviceAddress ��Ϊ0����geometry.triangles.transformData.deviceAddress �б�����뵽16�ֽڴ�С
			26.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_AABBS_KHR ��Ԫ�أ���1��geometry.aabbs.data.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																														   ��2�����geometry.aabbs.data.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																														   ��3��geometry.aabbs.data.deviceAddress ������뵽8�ֽ�
			27.��pInfos[i].pGeometries ���� pInfos[i].ppGeometries���κ�geometryTypeΪVK_GEOMETRY_TYPE_INSTANCES_KHR ��Ԫ�أ���1�����geometry.arrayOfPointers ΪVK_FALSE����geometry.instances.data.deviceAddress ������뵽16�ֽ�
																															   ��2�����geometry.arrayOfPointers ΪVK_TRUE����geometry.instances.data.deviceAddress ������뵽8�ֽ�
																															   ��3�����geometry.arrayOfPointers ΪVK_TRUE����geometry.instances.data.deviceAddress�ڴ��е�ÿ��Ԫ�ر�����뵽16�ֽ�
																															   ��4��geometry.instances.data.deviceAddress ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address
																															   ��5�����geometry.instances.data.deviceAddress ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
																															   ��6��geometry.instances.data.deviceAddress�ڴ��е�ÿ��VkAccelerationStructureInstanceKHR::accelerationStructureReference ������һ����Ч��ͨ��vkGetBufferDeviceAddress��ȡ��device address ����0
			28.commandBuffer ������һ��protected command buffer
			29.��pIndirectDeviceAddresses�е��κ�Ԫ�أ������buffer device address ��Ӧ��һ��non-sparse��buffer�����buffer����󶨵�һ�������������ĵ�����VkDeviceMemory������
			30.��pIndirectDeviceAddresses[i]�е��κ�Ԫ��,������pIndirectDeviceAddresses[i] ��pIndirectDeviceAddresses[i] + (pInfos[i].geometryCount �� pIndirectStrides[i]) - 1 ��device addresse ��������ͬbuffer��device address range��
			31.��pIndirectDeviceAddresses�е��κ�Ԫ�أ����Ӧ��buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ����
			32.pIndirectDeviceAddresses�е�ÿ��Ԫ�ر�����4�ı���
			33.pIndirectStrides�е�ÿ��Ԫ�ر�����4�ı���
			34.pIndirectDeviceAddresses�е��κ�Ԫ�����õ�ÿ��VkAccelerationStructureBuildRangeInfoKHR������һ����Ч��VkAccelerationStructureBuildRangeInfoKHR�ṹ
			35.pInfos[i].dstAccelerationStructure ������VkAccelerationStructureCreateInfoKHR::size ���ڵ��ڲ�ѯ�����������ص��ڴ��С��������vkGetAccelerationStructureBuildSizesKHR ����pBuildInfo = pInfos[i] �Լ�pMaxPrimitiveCounts = ppMaxPrimitiveCounts[i]
			36.ÿ��ppMaxPrimitiveCounts[i][j]��ֵ������ڵ���pIndirectDeviceAddresses[i] + (j �� pIndirectStrides[i])��λ��VkAccelerationStructureBuildRangeInfoKHR��primitiveCount

			*/

		}
	}


}

NS_TEST_END