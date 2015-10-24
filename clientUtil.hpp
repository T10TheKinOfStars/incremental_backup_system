#ifndef CLIENTUTIL_HPP
#define CLIENTUTIL_HPP

int getStatus(SmartSyncClient client, FileWorker* fworker);

void write2server(SmartSyncClient client, RFile &rfile, RFileMetadata &data);

void updatelocal(...);

void updateserver(...);

void process(int status);
#endif
