#pragma once

#include <GL\GL.h>
#include "glext.h"


// Framebuffer object
extern PFNGLGENFRAMEBUFFERSPROC                     pglGenFramebuffers;                      // FBO name generation procedure
extern PFNGLDELETEFRAMEBUFFERSPROC                  pglDeleteFramebuffers;                   // FBO deletion procedure
extern PFNGLBINDFRAMEBUFFERPROC                     pglBindFramebuffer;                      // FBO bind procedure
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC              pglCheckFramebufferStatus;               // FBO completeness test procedure
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pglGetFramebufferAttachmentParameteriv;  // return various FBO parameters
extern PFNGLGENERATEMIPMAPPROC                      pglGenerateMipmap;                       // FBO automatic mipmap generation procedure
extern PFNGLFRAMEBUFFERTEXTURE2DPROC                pglFramebufferTexture2D;                 // FBO texdture attachement procedure
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC             pglFramebufferRenderbuffer;              // FBO renderbuffer attachement procedure
// Renderbuffer object
extern PFNGLGENRENDERBUFFERSPROC                    pglGenRenderbuffers;                     // renderbuffer generation procedure
extern PFNGLDELETERENDERBUFFERSPROC                 pglDeleteRenderbuffers;                  // renderbuffer deletion procedure
extern PFNGLBINDRENDERBUFFERPROC                    pglBindRenderbuffer;                     // renderbuffer bind procedure
extern PFNGLRENDERBUFFERSTORAGEPROC                 pglRenderbufferStorage;                  // renderbuffer memory allocation procedure
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC          pglGetRenderbufferParameteriv ;           // return various renderbuffer parameters
extern PFNGLISRENDERBUFFERPROC                      pglIsRenderbuffer ;                       // determine renderbuffer object type

#define glGenFramebuffers                        pglGenFramebuffers
#define glDeleteFramebuffers                     pglDeleteFramebuffers
#define glBindFramebuffer                        pglBindFramebuffer
#define glCheckFramebufferStatus                 pglCheckFramebufferStatus
#define glGetFramebufferAttachmentParameteriv    pglGetFramebufferAttachmentParameteriv
#define glGenerateMipmap                         pglGenerateMipmap
#define glFramebufferTexture2D                   pglFramebufferTexture2D
#define glFramebufferRenderbuffer                pglFramebufferRenderbuffer

#define glGenRenderbuffers                       pglGenRenderbuffers
#define glDeleteRenderbuffers                    pglDeleteRenderbuffers
#define glBindRenderbuffer                       pglBindRenderbuffer
#define glRenderbufferStorage                    pglRenderbufferStorage
#define glGetRenderbufferParameteriv             pglGetRenderbufferParameteriv
#define glIsRenderbuffer                         pglIsRenderbuffer

struct FBO{
	GLuint fboId;
	GLuint rboId;
	GLuint texture;
	int width;
	int height;

	FBO(int w, int h):width(w),height(h){};
};

//run dis first
void initFBO();

//set the FBO width, height; generates a framebuffer object and associates it to a render buffer and a texture
void genFBO(FBO& fbo);