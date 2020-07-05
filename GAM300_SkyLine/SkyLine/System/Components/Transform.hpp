#pragma once
#include "BaseComponent.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/normal.hpp>

namespace Component
{
    class Transform : public BaseComponent
    {
	private:
		glm::quat Orientation_;
		glm::vec3 position_;
		glm::vec3 scale_;

		void updateVectors();

		glm::vec3 front_;
		glm::vec3 right_;
		glm::vec3 up_;

		// transform of a parent
		//example: a camera can parent itself to an object to mirror its movements
		const Transform * parentTransform_;

    public:
        COMPONENT_HASH(Transform)   // This macro generates our type hash we absolutely need it (It won't compile anyways if you don't add it)
        Transform(Actor* owner_);
        ~Transform();

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;
		virtual void Update(float dt);
		glm::vec3 getPosition(); // get position

		glm::vec3 getScale();
		void setScale(const glm::vec3& vec3);

		void setParent(const Transform* parentTransform);
		glm::quat getOrientation();
		// make it look at a dircection
		void lookAt(glm::vec3 direction); // make orientation look at this dir

		// Translation
		void translate(const glm::vec3 &v); //offset by an amount
		void goTo(const glm::vec3 &v);      //teleport a location BETTER

		// ROTATION
		  // orientation quat  is rotated about an angle
		void rotate(float angle, const glm::vec3 &axis);
		void yaw(float angle);
		void pitch(float angle);
		void roll(float angle);

		void setOrientation(const glm::quat& q);

		//get normalized vectors of the orientation
		glm::vec3 getFront();
		glm::vec3 getRight();
		glm::vec3 getUP();


		// CurrentOrientation = RotateTowards(CurrentOrientation, TargetOrientation, max angle for rotation * deltaTime );
		glm::quat RotateTowards(glm::quat q1, glm::quat q2, float  maxAngle);
		void RotateTowards(glm::quat q2, float  maxAngle);

		
		void RotateTowards(glm::vec3 dest);
		glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
		
    };
	
}
