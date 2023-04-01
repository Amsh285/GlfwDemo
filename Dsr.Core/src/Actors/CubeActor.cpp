#include "dsrpch.h"
#include "CubeActor.h"

namespace dsr
{
	namespace actors
	{
		std::shared_ptr<VaoAggregate> CubeActor::BuildCubeVaoAggregate() const
		{
			//TODO: check if this is set right after we can rotate stuff properly
			//especially texturecoors

			std::vector<float> vertexBuffer = {
				/* front face */
				-0.5f, -0.5f, 0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 0.0f, 1.0f, /*Normal*/
				0.5f, -0.5f, 0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 0.0f, 1.0f, /*Normal*/
				0.5f, 0.5f, 0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 0.0f, 1.0f, /*Normal*/
				-0.5f, 0.5f, 0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 0.0f, 1.0f, /*Normal*/

				/* back face */
				-0.5f, -0.5f, -0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 0.0f, -1.0f, /*Normal*/
				0.5f, -0.5f, -0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 0.0f, -1.0f, /*Normal*/
				0.5f, 0.5f, -0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 0.0f, -1.0f, /*Normal*/
				-0.5f, 0.5f, -0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 0.0f, -1.0f, /*Normal*/

				/* left face */
				-0.5f, -0.5f, -0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ -1.0f, 0.0f, 0.0f, /*Normal*/
				-0.5f, -0.5f, 0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ -1.0f, 0.0f, 0.0f, /*Normal*/
				-0.5f, 0.5f, 0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ -1.0f, 0.0f, 0.0f, /*Normal*/
				-0.5f, 0.5f, -0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ -1.0f, 0.0f, 0.0f, /*Normal*/

				/* right face */
				0.5f, -0.5f, -0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ 1.0f, 0.0f, 0.0f, /*Normal*/
				0.5f, -0.5f, 0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ 1.0f, 0.0f, 0.0f, /*Normal*/
				0.5f, 0.5f, 0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ 1.0f, 0.0f, 0.0f, /*Normal*/
				0.5f, 0.5f, -0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ 1.0f, 0.0f, 0.0f, /*Normal*/

				/* top face */
				-0.5f, 0.5f, -0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 1.0f, 0.0f, /*Normal*/
				0.5f, 0.5f, -0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ 0.0f, 1.0f, 0.0f, /*Normal*/
				0.5f, 0.5f, 0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 1.0f, 0.0f, /*Normal*/
				-0.5f, 0.5f, 0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ 0.0f, 1.0f, 0.0f, /*Normal*/

				/* bottom face */
				-0.5f, -0.5f, -0.5f, /*Vertexposition*/ 0.0f, 0.0f, /*Texturecoordinates*/ 0.0f, -1.0f, 0.0f, /*Normal*/
				0.5f, -0.5f, -0.5f, /*Vertexposition*/ 1.0f, 0.0f, /*Texturecoordinates*/ 0.0f, -1.0f, 0.0f, /*Normal*/
				0.5f, -0.5f, 0.5f, /*Vertexposition*/ 1.0f, 1.0f, /*Texturecoordinates*/ 0.0f, -1.0f, 0.0f, /*Normal*/
				-0.5f, -0.5f, 0.5f, /*Vertexposition*/ 0.0f, 1.0f, /*Texturecoordinates*/ 0.0f, -1.0f, 0.0f, /*Normal*/
			};

			std::vector<unsigned int> indices = {
				0, 1, 2, 0, 2, 3, /* front face */
				4, 5, 6, 4, 6, 7, /* back face */
				8, 9, 10, 8, 10, 11, /* left face */
				12, 13, 14, 12, 14, 15, /* right face */
				16, 17, 18, 16, 18, 19, /* top face */
				20, 21, 22, 20, 22, 23 /* bottom face */
			};

			VertexAttributeContainer attributes;
			attributes.Append(3); /*Vertexposition*/
			attributes.Append(2); /*Texturecoordinates*/
			attributes.Append(3); /*Normal*/

			return std::make_shared<VaoAggregate>(VaoAggregate::Build(vertexBuffer, indices, attributes));
		}
	}
}
