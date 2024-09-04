#include "MicroMapAndRayTraverseRayTracingTest.h"
NS_TEST_BEGIN

MicromapAndRayTraverseRayTracingTest::MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::run()
{
}

MicromapAndRayTraverseRayTracingTest::~MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::MicromapTest()
{
	/*
	���ٽṹ��֯ray tracing��Ҫ��geometry��Ȼ����һЩ����£��洢����֯һЩ��geometry��أ������������ε�geometry������Ϣ�����洦�ģ�micromap������֯��һЩ��Ӧ��ϸ�ֵ�΢�����ε���Ϣ�����Դ��� bottom level acceleration structure��ӵ�������geometry��ʱ��

	opacity micromap�洢���� intersection opacity ���μ�p3333������Ϣ

	displacement micromap�洢�ƶ�sub-triangle �������Ϣ ���μ�Displacement Micromap. p3324��

	����ʹ��micromap�Ĺ����Լ���������������һ��micromap
	*/

	VkMicromapEXT micromapEXT{};
	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };


	// Micromaps �μ�p3294
	{
		//����micromap
		VkMicromapBuildInfoEXT micromapBuildInfoEXT{};//�ýṹ���һЩ�����Ϣ��p3299
		micromapBuildInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
		micromapBuildInfoEXT.pNext = nullptr;
		micromapBuildInfoEXT.type = VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT;// VkMicromapTypeEXTֵָ��Ҫ������micromap����
		micromapBuildInfoEXT.flags = VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT;//VkBuildMicromapFlagBitsEXT���ֵλ����ָ������Ĳ���
		micromapBuildInfoEXT.mode = VK_BUILD_MICROMAP_MODE_BUILD_EXT;// VkBuildMicromapModeEXTֵָ��Ҫִ�еĲ���,VK_BUILD_MICROMAP_MODE_BUILD_EXT ָ��ʹ��ָ�������ݹ���micromap
		micromapBuildInfoEXT.dstMicromap = micromapEXT;//ָ��Ҫ������micromap�ľ��
		micromapBuildInfoEXT.usageCountsCount = 1;//ָ����������micromap��С��VkMicromapUsageEXT������
		VkMicromapUsageEXT micromapUsageEXT{};
		{
			micromapUsageEXT.count = 1;//Ϊmicromap��subdivisionLevel �Լ� format �����ʹ�ø�ʽ�������ε�����
			micromapUsageEXT.format = 0;//Ϊʹ�ø�ʽ��format
			/*
			VkOpacityMicromapFormatEXT��
			VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT:  ָ������micromap format��ÿ��subtriangle��Ӧ��һ��bitָ������ȫ��͸��������ȫ͸��
			VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT:  ָ������micromap format��ÿ��subtriangle��Ӧ������bit��������ͼ�p3333 ray traversal


			VkDisplacementMicromapFormatNV:
			VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV: ָ������micromap format��64��ֵ���滻��64��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV:  ָ������micromap format��128��ֵ���滻��128��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV:  ָ������micromap format��1024��ֵ���滻��128��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			*/
			micromapUsageEXT.subdivisionLevel = 0;//Ϊʹ�ø�ʽ�� subdivision level
			/*
			VkMicromapUsageEXT��Ч�÷�:
			1.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����1��format����ΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT���� VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 ��2�����formatΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 ��3�����formatΪVK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����1��format����ΪVK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV ���� VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 ��2��subdivisionLevel ����С�ڵ���VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/
		}
		micromapBuildInfoEXT.pUsageCounts = &micromapUsageEXT;//һ��VkMicromapUsageEXT ������ָ��
		micromapBuildInfoEXT.ppUsageCounts = VK_NULL_HANDLE;//һ��VkMicromapUsageEXT ������ָ�������ָ�룬��pUsageCountsֻ����һ����ΪVK_NULL_HANDLE
		micromapBuildInfoEXT.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//����micromap���ݵ� device ���� host�˵�const�ڴ��ַ
		micromapBuildInfoEXT.scratchData = VkDeviceOrHostAddressKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressKHR*/ };//Ϊ���ڹ����� scratch memory �� device ���� host�˵��ڴ��ַ
		//triangleArray�е�����
		{
			VkMicromapTriangleEXT micromapTriangleEXT{};
			micromapTriangleEXT.dataOffset = 0;//Ϊ�����������ݵ���ʼ�ֽ�ƫ����
			micromapTriangleEXT.format = 0;//Ϊ�������ε�subdivision level
			micromapTriangleEXT.subdivisionLevel = 0;//Ϊ�������ε�format

			/*
			VkMicromapTriangleEXT��Ч�÷�:
			1.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����1��format����ΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT���� VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 ��2�����formatΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 ��3�����formatΪVK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����1��format����ΪVK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV ���� VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 ��2��subdivisionLevel ����С�ڵ���VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/

		}
		micromapBuildInfoEXT.triangleArray = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����VkMicromapTriangleEXT ���ݵ� device ���� host�˵�const�ڴ��ַ
		micromapBuildInfoEXT.triangleArrayStride = 12;//ָ��triangleArray ������Ԫ��֮����ֽڲ���
		/*
		VkMicromapBuildInfoEXT��Ч�÷�:
		1.pUsageCounts��ppUsageCounts��ֻ��һ��Ϊ��Ч��ָ�룬����һ������ΪVK_NULL_HANDLE
		2.���typeΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����VkMicromapUsageEXT::format��VkMicromapTriangleEXT::format ��������Ч��VkOpacityMicromapFormatEXTֵ
		3.���typeΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����VkMicromapUsageEXT::format��VkMicromapTriangleEXT::format ��������Ч��VkDisplacementMicromapFormatNVֵ

		*/




		/*
		���ж� VkMicromapBuildInfoEXT::scratchData,VkMicromapBuildInfoEXT::dstMicromap, VkMicromapBuildInfoEXT::data�Լ�VkMicromapBuildInfoEXT::triangleArray��VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ����
		VkMicromapBuildInfoEXT::scratchData ��(VK_ACCESS_2_MICROMAP_READ_BIT_EXT | VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT)���з���
		VkMicromapBuildInfoEXT::dstMicromap ��VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT ���з���
		VkMicromapBuildInfoEXT::data�Լ�VkMicromapBuildInfoEXT::triangleArray ��VK_ACCESS_2_MICROMAP_READ_BIT_EXT ���з���
		*/
		vkCmdBuildMicromapsEXT(commandBuffer, 1, &micromapBuildInfoEXT);
		/*
		vkCmdBuildMicromapsEXT��Ч�÷�:
		1.���κ�pInfos[i]��dstMicromap ������VkMicromapCreateInfoEXT::size���ڵ��ڵ���vkGetMicromapBuildSizesEXT����pBuildInfo = pInfos[i]��ѯ���ص��ڴ��С���д���
		2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildMicromapModeEXT
		3.pInfos��ÿ��Ԫ�ص�dstMicromap������һ����Ч��VkMicromapEXT ���
		4.pInfos��ÿ��Ԫ�ص�type ����ƥ�䴴��dstMicromap ʱ��VkMicromapCreateInfoEXT::type
		5.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		6.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap���ܺ��κ�Ԫ��(������ͬԪ��)��scratchData�ĵײ��ڴ�ķ�Χ֮�����ص�
		7.��������ʵ�pInfos���κ�Ԫ�ص�scratchData�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		8.��pInfos��ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer�����Ѿ��󶨵�device memory
		9.���pInfos[i].mode ΪVK_BUILD_MICROMAP_MODE_BUILD_EXT������ pInfos[i].scratchData.deviceAddress �Լ� pInfos[i].scratchData.deviceAddress + N - 1 ֮������е�ַ��������ͬbuffer�ĵ�ַ��Χ�ڣ�����NΪ����vkGetMicromapBuildSizesEXT��������ͬVkMicromapBuildInfoEXT��primitive count���ص�VkMicromapBuildSizesInfoEXT::buildScratchSize
		10. pInfos[i]��data�Լ�triangleArray �漰����buffer������VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT����
		11.pInfos[i]��ÿ��pInfos[i].scratchData.deviceAddress �漰����buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
		12.��pInfos��ÿ��Ԫ�أ���scratchData.deviceAddress, data.deviceAddress�Լ�triangleArray.deviceAddress ��������Ч��ͨ��vkGetBufferDeviceAddress ��ȡ�ĵ�ַ
		13.��pInfos��ÿ��Ԫ�أ����scratchData.deviceAddress, data.deviceAddress�Լ�triangleArray.deviceAddress �漰��non-sparse��buffer�����buffer�����Ѿ��󶨵������������ĵ�����VkDeviceMemory����
		14.��pInfos��ÿ��Ԫ�أ���scratchData.deviceAddress ������VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment��������
		15.��pInfos��ÿ��Ԫ�أ���triangleArray.deviceAddress �Լ� data.deviceAddress������256 ��������

		*/


		//------------------------------------

		/*
		����һ�������Ҫ����micromap�����ݾͿ��Զ�����п��������ڿ���ǰ��Ҫ��ѯdst micromap���ڴ��С����
		*/

		//��ѯmicromap��С���� ����pMicromaps��Ԫ����VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ������VK_ACCESS_2_MICROMAP_READ_BIT_EXT����
		vkCmdWriteMicromapsPropertiesEXT(commandBuffer, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType,ָ����ѯ����*/, VkQueryPool{/*��������һ����Ч��VkQueryPool*/ }/*queryPool��ָ�������ѯ�����VkQueryPool*/, 0/*firstQuery,ָ����Ų�ѯ����ĵ�һ��query������*/);
		/*
		vkCmdWriteMicromapsPropertiesEXT��Ч�÷�:
		1.queryPool ������ƥ��queryType����
		2.��queryPool �Լ�firstQuery ָ����queries ������unavailable ��
		3.���ڴ���pMicrmaps��ÿ��micromap��buffer�����Ѿ��󶨵�device memory
		4.firstQuery + micromapCount ����С�ڵ���queryPool��queries������
		5.pMicromaps�е�����micromaps �����ڸ���ִ��ǰ������
		6.���queryTypeΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT�� pMicromaps�е�����micromaps ������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT ����
		7.queryType ����ΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT ����VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		*/




		VkCopyMicromapInfoEXT copyMicromapInfoEXT{};
		copyMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT;
		copyMicromapInfoEXT.pNext = nullptr;
		copyMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_CLONE_EXT;/* VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		VkCopyMicromapModeEXT:
		VK_COPY_MICROMAP_MODE_CLONE_EXT:  ����һ����src��dst��micromap��ֱ�ӿ�����dst micromap�����src����ͬ�Ĳ�������
		VK_COPY_MICROMAP_MODE_SERIALIZE_EXT: ��semi-opaque format���л�micromap�����л���ͷ����ʽ��Ϣ��p3308�������Ա����ݵ�ʵ�����¼���
		VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT:  ��semi-opaque format�����л���һ��micromap
		VK_COPY_MICROMAP_MODE_COMPACT_EXT:  ����һ����src��dst��ѹ���汾��Ϣ��dst �����Դ�С����Ϊ����src��������vkCmdWriteMicromapsPropertiesEXT���ص�ֵ����
		*/
		copyMicromapInfoEXT.src = VkMicromapEXT{/*��������һ����Ч��VkMicromapEXT*/ };//ָ��������source micromap
		copyMicromapInfoEXT.dst = micromapEXT;//ָ��������destination micromap
		/*
		VkCopyMicromapInfoEXT��Ч�÷�:
		1.mode ����ΪVK_COPY_MICROMAP_MODE_COMPACT_EXT ���� VK_COPY_MICROMAP_MODE_CLONE_EXT
		2.src micromap�����ڸ�����ִ��ǰ������
		3.���mode ΪVK_COPY_MICROMAP_MODE_COMPACT_EXT����src������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT����
		4.���ڴ���src�Լ�dst��buffer����󶨵�device memory��
		*/


		//����micromap ,   ��pInfo->src �Լ� pInfo->dst��VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ������VK_ACCESS_2_MICROMAP_READ_BIT_EXT ���� VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT����
		vkCmdCopyMicromapEXT(commandBuffer, &copyMicromapInfoEXT); //���ڴ���pInfo->src �Լ� pInfo->dst��buffer�����Ѿ��󶨵�device memory��




		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{};
		copyMicromapToMemoryInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT;
		copyMicromapToMemoryInfoEXT.pNext = nullptr;
		copyMicromapToMemoryInfoEXT.mode = VK_COPY_MICROMAP_MODE_SERIALIZE_EXT;//VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		copyMicromapToMemoryInfoEXT.src = micromapEXT;//ָ��������source micromap
		copyMicromapToMemoryInfoEXT.dst = VkDeviceOrHostAddressKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressKHR*/ };//Ϊ����micromap��dstination memory�� device ���� host�˵��ڴ��ַ
		/*
		VkCopyMicromapToMemoryInfoEXT��Ч�÷�:
		1.src micromap�����ڸ�����ִ��ǰ����
		2.dst�󶨵�memory�Ĵ�С������src���л��Ĵ�С���� vkWriteMicromapsPropertiesEXT ���� vkCmdWriteMicromapsPropertiesEXT ����query typeΪ VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT���ص�ֵ
		3.mode ����ΪVK_COPY_MICROMAP_MODE_SERIALIZE_EXT
		*/

		/*
		����һ��micromap���л���device memory ���� vkCopyMicromapToMemoryEXT������ͬ�����ֻ����������Ὣ���д��device memory�У���������Ա�vkCmdCopyMemoryToMicromapEXT ���� vkCopyMemoryToMicromapEXTʹ��
		��pInfo->src ����pInfo->dst �� VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage ͬ��

		��pInfo->src��VK_ACCESS_2_MICROMAP_READ_BIT_EXT���ʣ���pInfo->dst.deviceAddress�� VK_ACCESS_TRANSFER_WRITE_BIT����
		*/
		vkCmdCopyMicromapToMemoryEXT(commandBuffer, &copyMicromapToMemoryInfoEXT);
		/*
		vkCmdCopyMicromapToMemoryEXT��Ч�÷�:
		1.pInfo->dst.deviceAddress ������һ���󶨵�device memory����Ч��device address���������뵽256�ֽ�
		2.���pInfo->dst.deviceAddress ��ָ��buffer��non-sparse�����buffer����󶨵������������ĵ�����VkDeviceMemory����
		3.���ڴ���pInfo->src ��buffer����󶨵�device memory
		*/




		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{};
		copyMemoryToMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT;
		copyMemoryToMicromapInfoEXT.pNext = nullptr;
		copyMemoryToMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT;//VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		copyMemoryToMicromapInfoEXT.src = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����micromap��source memory�� device ���� host�˵�const�ڴ��ַ
		copyMemoryToMicromapInfoEXT.dst = micromapEXT;//ָ��������destination micromap
		/*
		VkCopyMemoryToMicromapInfoEXT��Ч�÷�:
		1.src��ָ��source memory�б������֮ǰͨ��vkCmdCopyMicromapToMemoryEXT���л�������
		2.mode ����ΪVK_COPY_MICROMAP_MODE_DESERIALIZE_EXT
		3.src�е����ݵı�����һ����destination physical device���ݵ�format ����vkGetDeviceMicromapCompatibilityEXT���ص���Ϣ
		4.dst ���ݴ�С�����Դ��ڵ���src�е����л����ݴ�С����

		*/


		/*
		����device memory�����л���һ��micromap����vkCopyAccelerationStructureToMemoryKHR������ͬ���
		��pInfo->src ����pInfo->dst ��  VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ��

		��pInfo->src.deviceAddress��VK_ACCESS_TRANSFER_READ_BIT���ʣ���pInfo->dst�� VK_ACCESS_2_MICROMAP_READ_BIT_EXT����

		��������Խ�������vkCmdCopyMicromapToMemoryEXT ���� vkCopyMicromapToMemoryEXT.������micromap
		*/
		vkCmdCopyMemoryToMicromapEXT(commandBuffer, &copyMemoryToMicromapInfoEXT);
		/*
		vkCmdCopyMemoryToMicromapEXT��Ч�÷�:
		1.pInfo->src.deviceAddress ������һ����Ч�İ󶨵�device memory��device address���ұ�����뵽256�ֽ�
		2.���pInfo->src.deviceAddress ��ָ��buffer��non-sparse�����buffer����󶨵������������ĵ�����VkDeviceMemory����
		3.���ڴ���pInfo->dst ��buffer����󶨵�device memory
		*/


		VkMicromapVersionInfoEXT micromapVersionInfoEXT{};
		micromapVersionInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT;
		micromapVersionInfoEXT.pNext = nullptr;
		uint8_t version = 0;
		micromapVersionInfoEXT.pVersionData = &version;//������vkCmdCopyMicromapToMemoryEXT���� vkCopyMicromapToMemoryEXT ִ���Ƕ���İ汾ͷ��Ϣ������ָ�룬ָ��2��VK_UUID_SIZE ��uint8_tֵ

		VkAccelerationStructureCompatibilityKHR cccelerationStructureCompatibilityKHR{};
		//���һЩ���л���micromap�Ƿ����device
		vkGetDeviceMicromapCompatibilityEXT(device, &micromapVersionInfoEXT, &cccelerationStructureCompatibilityKHR);// micromap ���Ա��뿪��
	}


	//Host Micromap Operations  �μ�p3314
	{
		/*
		��� micromapHostCommands���Կ�������ʵ��Ҳ�ṩ����host�˶�micromap�Ĳ���:
		
		host��							   ��Ӧ             device��
		vkBuildMicromapsEXT				    ->				vkCmdBuildMicromapsEXT
		vkCopyMicromapEXT					->				vkCmdCopyMicromapEXT
		vkCopyMicromapToMemoryEXT			->				vkCmdCopyMicromapToMemoryEXT
		vkCopyMemoryToMicromapEXT			->				vkCmdCopyMemoryToMicromapEXT
		vkWriteMicromapsPropertiesEXT		->				vkCmdWriteMicromapsPropertiesEXT
		

		host�˲���micromap��������ʵ�micromap����󶨵�host-visible���ڴ棬������micromap�����������������ݱ�������host�˵ĵ�ַ������device��
		*/

		VkMicromapBuildInfoEXT micromapBuildInfoEXT{/*��������һ����Ч��VkMicromapBuildInfoEXT*/};//ǰ���Ѿ��������ˣ����ﲻ�ٸ���

		//��host�˹���micromap  ,��Ч��vkCmdBuildMicromapsEXT����������ǰ������������ﲻ�ٸ����������������κ��ڴ���ʿ���
		vkBuildMicromapsEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, 1, & micromapBuildInfoEXT);
		/*
		vkBuildMicromapsEXT��Ч�÷�:
		1.���κ�pInfos[i]��dstMicromap ������VkMicromapCreateInfoEXT::size���ڵ��ڵ���vkGetMicromapBuildSizesEXT����pBuildInfo = pInfos[i]��ѯ���ص��ڴ��С���д���
		2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildMicromapModeEXT
		3.pInfos��ÿ��Ԫ�ص�dstMicromap������һ����Ч��VkMicromapEXT ���
		4.pInfos��ÿ��Ԫ�ص�type ����ƥ�䴴��dstMicromap ʱ��VkMicromapCreateInfoEXT::type
		5.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		6.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap���ܺ��κ�Ԫ��(������ͬԪ��)��scratchData�ĵײ��ڴ�ķ�Χ֮�����ص�
		7.��������ʵ�pInfos���κ�Ԫ�ص�scratchData�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		8.��pInfos��ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer�����Ѿ��󶨵�host-visible device memory
		9.pInfos�е�ÿ��Ԫ�أ�����Ԫ�ص�data.hostAddress���õı�������Ч��host memory
		10.pInfos�е�ÿ��Ԫ�أ�����Ԫ�ص�triangleArray.hostAddress���õı�������Ч��host memory
		11.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		12.���pInfos[i].mode ΪVK_BUILD_MICROMAP_MODE_BUILD_EXT������ pInfos[i].scratchData.hostAddress �Լ� pInfos[i].scratchData.hostAddress + N - 1 ֮������е�ַ������Ч��host memory������NΪ����vkGetMicromapBuildSizesEXT��������ͬVkMicromapBuildInfoEXT��primitive count���ص�VkMicromapBuildSizesInfoEXT::buildScratchSize
		13.pInfos�е�ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer����󶨵�memory������memory������multiple instances �Ϸ���
		*/



		VkCopyMicromapInfoEXT copyMicromapInfoEXT{/*��������һ����Ч��VkCopyMicromapInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//��host�˿�������ѹ��һ��micromap  ,��Ч��vkCmdCopyMicromapEXT
		vkCopyMicromapEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMicromapInfoEXT);
		/*
		vkCopyMicromapEXT��Ч�÷�:
		1.  VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.���ڴ���pInfo->src��pInfo->dst micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/


		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{/*��������һ����Ч��VkCopyMemoryToMicromapInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//host�˿��� host accessible memory ��һ��micromap����Ч��vkCmdCopyMemoryToMicromapEXT�����Խ����� vkCmdCopyMicromapToMemoryEXT ����vkCopyMicromapToMemoryEXT������micromap
		vkCopyMemoryToMicromapEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMemoryToMicromapInfoEXT);
		/*
		vkCopyMemoryToMicromapEXT��Ч�÷�:
		1. VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.pInfo->src.hostAddress��������Ч�� host pointer�����������뵽16�ֽ�
		4.���ڴ���pInfo->dst micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���

		*/


		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{/*��������һ����Ч��VkCopyMicromapToMemoryInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//host�˿���һ��micromap��host accessible memory����Ч��vkCmdCopyMicromapToMemoryEXT���ýӿ�������Ա�vkCmdCopyMemoryToMicromapEXT ���� vkCopyMemoryToMicromapEXTʹ��
		vkCopyMicromapToMemoryEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMicromapToMemoryInfoEXT);
		/*
		vkCopyMicromapToMemoryEXT��Ч�÷�:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.pInfo->dst.hostAddress��������Ч�� host pointer�����������뵽16�ֽ�
		4.���ڴ���pInfo->src micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/



		uint32_t needSize = 0;
		//host�˲�ѯmicromap�Ĵ�С����
		VkMicromapEXT micromapEXT{/*��������һ����Ч��VkMicromapEXT*/ };
		//��Ч�� vkCmdWriteMicromapsPropertiesEXT
		vkWriteMicromapsPropertiesEXT(device, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType��ָ����ѯ����*/, sizeof(needSize)/*dataSize��pData�е��ֽڴ�С*/, &needSize/*pData,Ϊ�û���������ڴ�Ų�ѯ������ڴ�ָ��*/, sizeof(needSize)/*stride,ΪpData�е����Ĳ�ѯ���֮����ֽڲ���*/);
		/*
		vkWriteMicromapsPropertiesEXT��Ч�÷�:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.pMicromaps�е�����micromap�����Ѿ��ڸ������ִ��ǰ����
		3.pMicromaps�е�����micromap���queryTypeΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT�������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT����
		4.queryType����ΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT ���� VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		5.���queryTypeΪVK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT����1��stride ����ΪVkDeviceSize�����ֽڴ�С��������
																		  ��2��pData������һ��ָ��VkDeviceSize������
		6.dataSize ������ڻ����micromapCount*stride
		7.��������pMicromaps��ÿ��micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/



		//Displacement Micromap �μ�p3324
		{
			//����� p3324 - p3327
		}

	}
}

void MicromapAndRayTraverseRayTracingTest::RayTraverseTest()
{
	/*
	ray traversal������ٽṹ��geometry��ray���ཻ��
	
	ray traversal��ͨ��vulkan APIֱ�ӿ�ʼ��������Ҫһ��shaderִ��OpRayQueryProceedKHR����һ�� pipeline trace ray ָ�

	��rayTracingPipeline ���Կ�������OpTraceRayKHR ��������ray tracing���� rayQuery���Կ�������OpRayQueryProceedKHR�������κ�shader stageʹ�á�
	*/


	//Ray Intersection Candidate Determination  �μ�p3327
	{
		/*
		ray tracingһ����ʼ��ray���Ȼ��ж��Ƿ���ܺ�instance�ཻ��Ȼ����ȥ�ж��Ƿ���ܺ�instance�е�geometry�ཻ��

		һ���жϿ��ܺ�ĳ��geometry�ཻ����Ὣ��geometry��ͼԪ�Ķ���Ӽ��ٽṹ�Ķ���ռ�任��ray�ķ�����Ϊ-z���ray�ռ��У�Ȼ��Ѱ���ཻ��ѡ�㣬
		����ͼԪ��ray�ཻ��ѡ���������ray�ռ���x��yΪ0��zΪһ��ֵ�ĵ�
		
		һ��ȷ���˸ñ�ѡ���㣬������ν������²���:
		1. Ray Intersection Culling
		2. Ray Intersection Confirmation
		3. Ray Closest Hit Determination
		4. Ray Result Determination
		*/

	}


	// Watertightness  �μ�p3330   ��һЩ����������߹���ߵ�ͼԪ�����뱣֤��Щ��������߹���߲��ܱ�ray���ж��


	//Ray Intersection Culling  �μ�p3330
	{
		/*
		ȷ�����ཻ��ѡ���ᾭ��һϵ��˳�򲻶���cull����Ȼ������ȷ���ཻ�㡣
		*/


		//Ray Primitive Culling  �μ�p3330
		{
			/*
			���rayTraversalPrimitiveCulling ���� rayQuery ���Կ������������ray flags��ָ��SkipTrianglesKHR ����SkipAABBsKHR(����ֻ����һ��)��ָ����ray�������λ���aabbs�ཻʱ���ô��ཻ�Ľ��㴦����ֹ������Ըý���������������

			Ҳ�����ڴ���ray tracing pipeline��ʱ��ָ��VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR ���� VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR���ﵽ��ͬ��Ч����
			
			*/
		}

		//Ray Mask Culling  �μ�p3331
		{
			/*
			������ray tracing��Cull Mask��VkAccelerationStructureInstanceKHR::mask�Ĳ������mask & Cull Mask == 0 ʱָ���ü��ٽṹʵ����ray���ɼ����˴��ཻ��ֹ�����ٽ��к���������
			*/
		}

		//Ray Face Culling  �μ�p3331
		{
			/*
			�ڻ���������ʱ�������ray�ķ���ȥ��ͼԪ���棨����ͼԪ������ray�ռ��и���rasterization�½ڶ������������㹫ʽ�������ֵΪ���������� HitKindKHR ������ΪHitKindFrontFacingTriangleKHR���������ΪHitKindBackFacingTriangleKHR��

			���ray��OpRayQueryProceedKHR���У����������ʱOpRayQueryGetIntersectionFrontFaceKHR�᷵��true����֮Ϊfalse��

			�����ray flags������ CullBackFacingTrianglesKHR�����ڻ��б����ʱ�򣬻������������ CullFrontFacingTrianglesKHR����ǰ��ֻ��ʹ��һ�������ڻ��������ʱ�򣬴˴λ��в�����ֹ�����ٽ��к������������VkAccelerationStructureInstanceKHR::flags��������VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR������Է�ת�������������Ļ�����Ϊ����Ļ��У���֮һ����


			���VkAccelerationStructureInstanceKHR::flags��������VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR������Թر�ray face culling
			*/
		}

		//Ray Opacity Culling  �μ�p3332
		{
			/*
			��ray taversal�����У����geometryΪ͸���ģ���Opaque�ģ����geometry���ܻᱻ������

			geometry��Opeque������������ VkAccelerationStructureGeometryKHR::flags �Ƿ����VK_GEOMETRY_OPAQUE_BIT_KHR������
			���geometry����Opaque micromap�����һ��ʹ��micromap��˵�������ԣ���Ȼ����VkAccelerationStructureInstanceKHR::flags
			���Ƿ����VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR ����VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR ������Opaque����
			��������ray flags�а��� OpaqueKHR ���� NoOpaqueKHR ָ�����е�geometry�Ƿ��ǲ�͸���ġ�

			���ray�� OpRayQueryProceedKHR����trace���� OpRayQueryGetIntersectionCandidateAABBOpaqueKHR���������ж��Ƿ��ཻ��һ��Opaque��AABB������Ƿ���true�����򷵻�false��

			���ж���Opaque���Ժ����ray flags�а���CullOpaqueKHR�����opaque geometry���ཻ����ֹ�����ٽ��к����������������CullNoOpaqueKHR�����non-opaque geometry���ཻ����ֹ��
			���ٽ��к���������ray flags��OpaqueKHR, NoOpaqueKHR, CullOpaqueKHR, �Լ� CullNoOpaqueKHR ֻ�ܻ���ʹ�á�

			*/



		
		}


		//Ray Opacity Micromap  �μ�p3333
		{
			/*
			���VkAccelerationStructureInstanceKHR::flags�в���VK_GEOMETRY_INSTANCE_DISABLE_OPACITY_MICROMAPS_EXT�����ʹ��micromap����geometry��opaque���Խ���ϸ���ȵĿ��ơ�

			�����p3334
			
			*/
		}

	}



	//Ray Intersection Confirmation  �μ�p3334
	{
		//AABB Intersection Candidates  �μ�p3335

		//Triangle and Generated Intersection Candidates  �μ�p3335
		{
			/*
			�����ཻ��opaque���ԣ���ǰ��ray opaque culling����Ҫ�����shader������ȷ���Ƿ��������˴��ཻ�ı�ѡ�㣬�ò������Զ���ͬ��ѡ��ִ�ж�γ���ָ��VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR��

			����ཻ��opaque����Ϊopaque����˴θ�ȷ�ϸñ�ѡ�㣬Ȼ������һ�׶ν��к�������

			����ཻ��opaque����Ϊnon-opaque�������shader������OpIgnoreIntersectionKHR������ֹ�Ըñ�ѡ��Ĵ������ any-hit shaderΪ VK_SHADER_UNUSED_KHR����ȷ�ϸñ�ѡ�㣬Ȼ������һ�׶ν��к�������
			
			���ray ��OpRayQueryProceedKHR ���У������ OpRayQueryConfirmIntersectionKHRȷ�ϸñ�ѡ�㣬Ȼ��Ը�ray trace��������OpRayQueryProceedKHR���������OpRayQueryTerminateKHR��ֱ����ֹ�Ըñ�ѡ��Ĵ���
			*/
		}

	}

	//Ray Closest Hit Determination  �μ�p3336
	{
		/*
		����ray flags��������TerminateOnFirstHitKHR���������ֱ������geometry����������ȷ������ֹ�˻��б�ѡ���ҳ�����Ļ��е㣨��ѡ�㶼����-z�ᣬ���������Ϊz���ĵ㣩Ϊֹ��
		*/
	}

	//Ray Result Determination  �μ�p3336
	{
		//һ���ཻ��ѡ������������׶λ���ǿ����ֹ��ray trace�������յĽ����ȷ���ˣ��Խ���ľ���������p3336
	}
}

void MicromapAndRayTraverseRayTracingTest::RayTracingTest()
{
	/*
	��ray tracing pipeline�У�ray tracing��ִ�й��̻ᴥ������shader stages��ray tracing pipeline ����VkBuffer�д��ݸ�ray tracing�������ڱ����ļ��ٽṹ��geometry֮��Ĺ��߳�Ϊshader binding table��

	 OpExecuteCallableKHR ������ray tracing���������ڴ���һ�� callable shader��

	 ray tracing�漰��shader stageΪ single-ray programming model��һ��ֻ����һ��ray
	
	*/


	//Shader Call Instructions  �μ�p3339
	{
		/*
		shader call��һ��ָ��������κεط�����һ����ͬ��shader stage����ִ�С�
		��Щָ��Ϊ:
		OpTraceRayKHR :  ���ܴ��� intersection, any-hit, closest hit, ���� miss shaders,
		OpTraceRayMotionNV : ���ܴ��� invoke intersection, any-hit, closest hit, ���� miss shaders,
		OpReportIntersectionKHR : ���ܴ��� any-hit shaders
		OpExecuteCallableKHR : ���� callable shader.
		OpHitObjectTraceRayNV, OpHitObjectTraceRayMotionNV, �Լ� OpHitObjectExecuteShaderNV :  ���ܴ���intersection, any-hit, closest hit, miss, ���� callable shaders.

		��Щָ������ڵݹ���ã����ݹ������ maxRecursionDepth ���� maxRayRecursionDepth ����
		

		invocation repack ָ��Ϊ ray tracing ָ����ܻ����ִ�е�һ����ã������������subgroup����ԭ��ͬһsubgroup��SubgroupLocalInvocationId����Щָ��ΪOpTraceRayKHR, OpTraceRayMotionNV, OpReorderThreadWithHintNV, OpReorderThreadWithHitObjectNV, OpReportIntersectionKHR, �Լ� OpExecuteCallableKHR
		�������subgroup��SubgroupSize, SubgroupLocalInvocationId, SMIDNV, WarpIDNV,�Լ�SubgroupEqMask, SubgroupGeMask, SubgroupGtMask, SubgroupLeMask, SubgroupLtMask������Ҫ�ı䡣������ray tracing�����У���Щ������Ҫ��Volatile
		
		*/

	}

	//Ray Tracing Commands �μ�p3340
	{
		/*
		ray tracing commands ��¼��command buffer�У�ִ����queue�У������󶨵�ray tracing pipeline���й�����
		
		*/

		VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };
		VkBuffer raygenShaderBindingTableBuffer{/*��������һ����Ч��VkBuffer*/ };
		VkBuffer missShaderBindingTableBuffer{/*��������һ����Ч��VkBuffer*/ };
		VkBuffer hitShaderBindingTableBuffer{/*��������һ����Ч��VkBuffer*/ };
		VkBuffer callableShaderBindingTableBuffer{/*��������һ����Ч��VkBuffer*/ };


		//dispatch ray tracing,   ִ�и������һ������ width �� height �� depth ��ray��ray ������ᱻ��װ
		vkCmdTraceRaysNV(commandBuffer, 
			raygenShaderBindingTableBuffer/*raygenShaderBindingTableBuffer,��������ray generation shader stage��shader binding table data.*/, 0/*raygenShaderBindingOffset��raygenShaderBindingTableBuffer�����ݵ���ʼ�ֽ�ƫ����*/,
			missShaderBindingTableBuffer/*missShaderBindingTableBuffer,��������miss shader stage��shader binding table data.*/, 0/*missShaderBindingOffset�� missShaderBindingTableBuffer�����ݵ���ʼ�ֽ�ƫ����*/,1/*missShaderBindingStride,ΪmissShaderBindingTableBuffer ��ÿ��shader binding table���ֽ�����С.*/,
			hitShaderBindingTableBuffer/*hitShaderBindingTableBuffer,��������hit shader stage��shader binding table data.*/, 0/*hitShaderBindingOffset��hitShaderBindingTableBuffer�����ݵ���ʼ�ֽ�ƫ����*/, 1/*hitShaderBindingStride,ΪhitShaderBindingTableBuffer ��ÿ��shader binding table���ֽ�����С.*/,
			callableShaderBindingTableBuffer/*callableShaderBindingTableBuffer,��������callable shader stage��shader binding table data.*/, 0/*callableShaderBindingOffset�� callableShaderBindingTableBuffer�����ݵ���ʼ�ֽ�ƫ����*/, 1/*callableShaderBindingStride,ΪcallableShaderBindingTableBuffer ��ÿ��shader binding table���ֽ�����С.*/,
			1/*width,Ϊray trace query dimensions��width.*/, 1/*height,Ϊray trace query dimensions��height.*/, 1/*depth,Ϊray trace query dimensions��depth.*/);
		/*
		vkCmdTraceRaysNV��Ч�÷�:
		1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
																												��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
		4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
		13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
		15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
		23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
		24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
																							  ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
		25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
		26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
		27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
		28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
		29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
		30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
																					��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
																					��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
																					��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
		31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
		32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
		37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
		38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
														  ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
		39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
		40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
		41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
		42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
		43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
		45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
		52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
		53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  ��2��VkImageView��format����ֻ����һ��component
		55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
		56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
		57.�����һ������ΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
		58.�κθõ������õ�shader group handle �����Ѿ��ڵ�ǰ�󶨵�ray tracing pipeline�в�ѯ����
		59.����󶨵�tracing pipeline ��VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR ��̬״̬�����������������ڵ�ǰ�������֮ǰ���� vkCmdSetRayTracingPipelineStackSizeKHR��
		60.commandBuffer ���벻����protected command buffer��
		61.����������һ����shader invocation��ִ�е�pipeline trace ray instruction�ĵݹ���ȳ����˴�����pipeline��maxRecursionDepth��
		62.���raygenShaderBindingTableBuffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		63.raygenShaderBindingOffset ����С�ڵ���raygenShaderBindingTableBuffer�Ĵ�С���ұ�����VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı�����
		64.���missShaderBindingTableBuffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		65.missShaderBindingOffset ����С�ڵ���missShaderBindingTableBuffer�Ĵ�С���ұ�����VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı�����
		66.���hitShaderBindingTableBuffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		67.hitShaderBindingOffset ����С�ڵ���hitShaderBindingTableBuffer�Ĵ�С���ұ�����VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı�����
		68.���callableShaderBindingTableBuffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		69.callableShaderBindingOffset ����С�ڵ���callableShaderBindingTableBuffer�Ĵ�С���ұ�����VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı�����
		70.missShaderBindingStride��hitShaderBindingStride�Լ�callableShaderBindingStride ������VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupHandleSize�ı������Ҷ�����С�ڵ���VkPhysicalDeviceRayTracingPropertiesNV::maxShaderGroupStride��
		71.width��height�Լ�depth�����ӦС�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]��
		*/


		VkStridedDeviceAddressRegionKHR raygenShaderBindingTable{};
		raygenShaderBindingTable.deviceAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };
		raygenShaderBindingTable.stride = 3;
		raygenShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR missShaderBindingTable{};
		missShaderBindingTable.deviceAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };
		missShaderBindingTable.stride = 3;
		missShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR hitShaderBindingTable{};
		hitShaderBindingTable.deviceAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };
		hitShaderBindingTable.stride = 3;
		hitShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR callableShaderBindingTable{};
		callableShaderBindingTable.deviceAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };
		callableShaderBindingTable.stride = 3;
		callableShaderBindingTable.size = 3;


		//dispatch ray tracing,   ִ�и������һ������ width �� height �� depth ��ray��ray ������ᱻ��װ
		vkCmdTraceRaysKHR(commandBuffer,
			&raygenShaderBindingTable,
			&missShaderBindingTable,
			&hitShaderBindingTable,
			&callableShaderBindingTable,
			1/*width,Ϊray trace query dimensions��width.*/, 1/*height,Ϊray trace query dimensions��height.*/, 1/*depth,Ϊray trace query dimensions��depth.*/);
		/*
		vkCmdTraceRaysKHR��Ч�÷�:
		1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
																												��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
		4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
		13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
		15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
		22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
		23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
		24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
																							  ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
		25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
		26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
		27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
		28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
		29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
		30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
																					��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
																					��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
																					��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
		31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
		32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
		37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
		38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
														  ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
		39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
		40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
		41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
		42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
		43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
		45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
		52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
		53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  ��2��VkImageView��format����ֻ����һ��component
		55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
		56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
		57.�����һ������ΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
		58.�κθõ������õ�shader group handle �����Ѿ��ڵ�ǰ�󶨵�ray tracing pipeline�в�ѯ����
		59.����󶨵�tracing pipeline ��VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR ��̬״̬�����������������ڵ�ǰ�������֮ǰ���� vkCmdSetRayTracingPipelineStackSizeKHR��
		60.����������һ����shader invocation��ִ�е�pipeline trace ray instruction�ĵݹ���ȳ����˴�����pipeline��maxPipelineRayRecursionDepth��
		61.commandBuffer ���벻����protected command buffer��
		62.pRayGenShaderBindingTable��size ���������stride
		63.���pRayGenShaderBindingTable->deviceAddress ���Ե�buffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		64.pRayGenShaderBindingTable->deviceAddress ���Ե�buffer ������VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR ����
		65.pRayGenShaderBindingTable->deviceAddress ������VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı���
		66.���pMissShaderBindingTable->deviceAddress ���Ե�buffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		67.pMissShaderBindingTable->deviceAddress ���Ե�buffer ������VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR ����
		68.pMissShaderBindingTable->deviceAddress ������VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı���
		69.pMissShaderBindingTable->stride ������VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment�ı�������С�ڵ���VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		70.���pHitShaderBindingTable->deviceAddress ���Ե�buffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		71.pHitShaderBindingTable->deviceAddress ���Ե�buffer ������VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR ����
		72.pHitShaderBindingTable->deviceAddress ������VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı���
		73.pHitShaderBindingTable->stride ������VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment�ı�������С�ڵ���VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		74.���pCallableShaderBindingTable->deviceAddress ���Ե�buffer ��non-sparse���������󶨵������������ĵ�����VkDeviceMemory�����ϡ�
		75.pCallableShaderBindingTable->deviceAddress ���Ե�buffer ������VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR ����
		76.pCallableShaderBindingTable->deviceAddress ������VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment�ı���
		77.pCallableShaderBindingTable->stride ������VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment�ı�������С�ڵ���VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		78.�����ǰ�󶨵�ray tracing pipeline �԰���VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ����VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR ��������pHitShaderBindingTable->deviceAddress ����Ϊ0
		79.�����ǰ�󶨵�ray tracing pipeline �԰���VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR ��������pMissShaderBindingTable->deviceAddress ָ����shader group handle ����Ϊ0
		80.�����ǰ�󶨵�ray tracing pipeline �԰���VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR ����VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ��VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ����VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR ������ ������ִ��һ��any-hit shader��Ϊ�����������з��ʵ� pHitShaderBindingTable->deviceAddress ָ����table�е�ʵ�� ��������Ϊ0
		81.�κα���������һ��geometryTypeΪVK_GEOMETRY_TYPE_TRIANGLES_KHR��geometry�н��з��ʵ� pHitShaderBindingTable->deviceAddress ָ����table�е��κ� ��0 hit shader group ʵ�������VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR ����
		82.�κα���������һ��geometryTypeΪVK_GEOMETRY_TYPE_AABBS_KHR��geometry�н��з��ʵ� pHitShaderBindingTable->deviceAddress ָ����table�е��κ� ��0 hit shader group ʵ�������VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR ����
		83.width��height�Լ�depth�����ӦС�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0] �� VkPhysicalDeviceLimits::maxComputeWorkGroupSize[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]  �� VkPhysicalDeviceLimits::maxComputeWorkGroupSize[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2] �� VkPhysicalDeviceLimits::maxComputeWorkGroupSize[2]��
		84.width �� height �� depth ����С�ڵ��� VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxRayDispatchInvocationCount	

		*/



	}

}

NS_TEST_END