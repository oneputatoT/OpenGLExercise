#version 330 core

out vec4 FragColor;

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};


struct LightDirectional
{
	vec3 dir;
	vec3 color;
};

struct LightPoint
{
	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
};

struct LightSpot
{
	vec3 dir;
	vec3 position;
	vec3 color;

	float cosphyInner;
	float cosphyOutter;
};


//in vec4 textColor;
in vec2 TexCord;
in vec3 Normal;
in vec3 FragPos;

//贴图纹理
uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform Material material;     //声明结构体


//uniform vec3 objColor;
uniform vec3 ambientColor;	
uniform float mixStrong;

//uniform vec3 lightPos;
//uniform vec3 lightColor;

uniform vec3 cameraPos;
//uniform vec3 specularColor;

//LightDirection
uniform LightDirectional lightDirectional;

//LightPoint
uniform LightPoint lightPoint0;
uniform LightPoint lightPoint1;
uniform LightPoint lightPoint2;
uniform LightPoint lightPoint3;

//lightSpot
uniform LightSpot lightSpot;


//LightDirection
vec3 CalcLightDirectional(LightDirectional light,vec3 normal,vec3 viewDir,vec3 objColor,float speColor)
{
	vec3 diffuse = max(dot(light.dir,normal),0)*objColor*light.color;

	vec3 reflectDir = normalize(reflect(-light.dir,normal));
	vec3 specular = pow(max(dot(reflectDir,viewDir),0),material.shininess) * light.color * speColor;

	vec3 result = vec3(diffuse+specular);
	return result;
}

vec3 CalcLightPoint(LightPoint light,vec3 normal,vec3 viewDir,vec3 objColor,float speColor)
{
	float dist = length(light.position-FragPos);
	float attenuation = 1.0f/(light.constant + light.linear*dist + light.quadratic*(dist*dist));  //点光源的衰减

	vec3 lightDir = normalize(light.position-FragPos);

	vec3 diffuse = max(dot(lightDir,normal),0) * objColor * light.color;

	vec3 reflectDir = normalize(reflect(-lightDir,normal));
	vec3 specular = pow(max(dot(reflectDir,viewDir),0),material.shininess) * light.color * speColor;

	vec3 result = vec3(diffuse+specular)*attenuation;

	return result;
}


vec3 CalcLightSpot(LightSpot light,vec3 normal,vec3 viewDir,vec3 objColor,float speColor)
{
	vec3 lightDir = normalize(light.position-FragPos);

	vec3 reflectDir = normalize(reflect(-lightDir,normal));

	vec3 diffuse = max(dot(lightDir,normal),0) * light.color * objColor;
	vec3 specular = pow(max(dot(reflectDir,viewDir),0),material.shininess) * light.color * speColor;

	float cosTheta = dot(-lightDir,-light.dir);
	float spotRatio;
	if(cosTheta>light.cosphyInner)
	{
		spotRatio = 1.0f;
	}
	else if(cosTheta>light.cosphyOutter)
	{
		spotRatio = clamp((light.cosphyOutter-cosTheta)/(light.cosphyOutter-light.cosphyInner),0.0f,1.0f);
	}
	else
	{
		spotRatio = 0;
	}

	vec3 result = diffuse + specular;
	return result*spotRatio;
}


void main()
{			
	
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(cameraPos-FragPos);

	vec3 objColor = texture(material.diffuse,TexCord).xyz;
	float spcColor = texture(material.specular,TexCord).r;


	vec3 ambient = objColor*ambientColor;

	vec3 finalColor;
	finalColor += CalcLightDirectional(lightDirectional,normal,viewDir,objColor,spcColor);
	finalColor += CalcLightPoint(lightPoint0,normal,viewDir,objColor,spcColor);
	finalColor += CalcLightPoint(lightPoint1,normal,viewDir,objColor,spcColor);
	finalColor += CalcLightPoint(lightPoint2,normal,viewDir,objColor,spcColor);
	finalColor += CalcLightPoint(lightPoint3,normal,viewDir,objColor,spcColor);
	finalColor += CalcLightSpot(lightSpot,normal,viewDir,objColor,spcColor);
	

	FragColor = vec4(finalColor+ambient,1.0f);
}	  