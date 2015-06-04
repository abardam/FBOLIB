#include <Windows.h>
#include <GL\glut.h>
#include <iostream>

//need this to get function prototypes
#define GL_GLEXT_PROTOTYPES
#include "glext.h"

#include "fbolib.h"

// Framebuffer object
PFNGLGENFRAMEBUFFERSPROC                     pglGenFramebuffers						= 0;				// FBO name generation procedure
PFNGLDELETEFRAMEBUFFERSPROC                  pglDeleteFramebuffers						= 0;				// FBO deletion procedure
PFNGLBINDFRAMEBUFFERPROC                     pglBindFramebuffer						= 0;				// FBO bind procedure
PFNGLCHECKFRAMEBUFFERSTATUSPROC              pglCheckFramebufferStatus					= 0;				// FBO completeness test procedure
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pglGetFramebufferAttachmentParameteriv	= 0;				// return various FBO parameters
PFNGLGENERATEMIPMAPPROC                      pglGenerateMipmap							= 0;				// FBO automatic mipmap generation procedure
PFNGLFRAMEBUFFERTEXTURE2DPROC                pglFramebufferTexture2D					= 0;				// FBO texdture attachement procedure
PFNGLFRAMEBUFFERRENDERBUFFERPROC             pglFramebufferRenderbuffer				= 0;				// FBO renderbuffer attachement procedure
// Renderbuffer object																	
PFNGLGENRENDERBUFFERSPROC                    pglGenRenderbuffers						= 0;				// renderbuffer generation procedure
PFNGLDELETERENDERBUFFERSPROC                 pglDeleteRenderbuffers					= 0;				// renderbuffer deletion procedure
PFNGLBINDRENDERBUFFERPROC                    pglBindRenderbuffer						= 0;				// renderbuffer bind procedure
PFNGLRENDERBUFFERSTORAGEPROC                 pglRenderbufferStorage					= 0;				// renderbuffer memory allocation procedure
PFNGLGETRENDERBUFFERPARAMETERIVPROC          pglGetRenderbufferParameteriv 			= 0;				 // return various renderbuffer parameters
PFNGLISRENDERBUFFERPROC                      pglIsRenderbuffer 						= 0;				 // determine renderbuffer object type

//vars
bool useFBO, FBOinit = false;

void initFBO(){
	glGenFramebuffers                     = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
    glDeleteFramebuffers                  = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
    glBindFramebuffer                     = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
    glCheckFramebufferStatus              = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
    glGenerateMipmap                      = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
    glFramebufferTexture2D                = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
    glFramebufferRenderbuffer             = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
    glGenRenderbuffers                    = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
    glDeleteRenderbuffers                 = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
    glBindRenderbuffer                    = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
    glRenderbufferStorage                 = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
    glGetRenderbufferParameteriv          = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
    glIsRenderbuffer                      = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
	if(glGenFramebuffers && glDeleteFramebuffers && glBindFramebuffer && glCheckFramebufferStatus &&
           glGetFramebufferAttachmentParameteriv && glGenerateMipmap && glFramebufferTexture2D && glFramebufferRenderbuffer &&
           glGenRenderbuffers && glDeleteRenderbuffers && glBindRenderbuffer && glRenderbufferStorage &&
           glGetRenderbufferParameteriv && glIsRenderbuffer)
    {
        std::cout << "Video card supports GL_ARB_framebuffer_object." << std::endl;
		useFBO = true;
    }
    else
    {
        std::cout << "Video card does NOT support GL_ARB_framebuffer_object." << std::endl;
		useFBO = false;
    }

	FBOinit = true;
}

void genFBO(FBO& fbo){

	if(!FBOinit) initFBO();

	// create a texture object
	glGenTextures(1, &(fbo.texture));
    glBindTexture(GL_TEXTURE_2D, fbo.texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fbo.width, fbo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &fbo.fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.fboId);

	glGenRenderbuffers(1, &fbo.rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, fbo.rboId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fbo.width, fbo.height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // attach a texture to FBO color attachement point
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo.texture, 0);
	// attach a renderbuffer to depth attachment point
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo.rboId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}