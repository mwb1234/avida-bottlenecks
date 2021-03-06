//
//  ViewerListener.h
//  avida/apps/viewer-macos
//
//  Created by David Bryson on 11/11/10.
//  Copyright 2010-2011 Michigan State University. All rights reserved.
//  http://avida.devosoft.org/viewer-macos
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
//  following conditions are met:
//  
//  1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the
//      following disclaimer.
//  2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//      following disclaimer in the documentation and/or other materials provided with the distribution.
//  3.  Neither the name of Michigan State University, nor the names of contributors may be used to endorse or promote
//      products derived from this software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY MICHIGAN STATE UNIVERSITY AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL MICHIGAN STATE UNIVERSITY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Authors: David M. Bryson <david@programerror.com>
//

#import <Foundation/Foundation.h>

#include "avida/viewer.h"

@class ViewerMap;
@class ViewerUpdate;


@protocol ViewerListener
@property (readonly) Avida::Viewer::Listener* listener;
@optional
- (void) handleMap:(ViewerMap*)pkg;
- (void) handleUpdate:(ViewerUpdate*)pkg;
@end


@interface ViewerMap : NSObject {
  Avida::Viewer::Map* m_map;
}
- (id) initWithMap:(Avida::Viewer::Map*)map;
@property (readonly) Avida::Viewer::Map* map;
@end;


@interface ViewerUpdate : NSObject {
  int m_update;
}
- (id) initWithUpdate:(int)update;
@property (readonly) int update;
@end


class MainThreadListener : public Avida::Viewer::Listener
{
private:
  id m_target;
  
public:
  MainThreadListener(id <ViewerListener> target) : m_target(target) { ; }
  
  bool WantsMap() { return true; }
  bool WantsUpdate() { return true; }
  
  void NotifyMap(Avida::Viewer::Map* map);
  void NotifyUpdate(int update);
};
