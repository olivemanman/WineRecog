clear all; close all; clc;

% load train dataset and labels
traindata = '..\..\..\..\..\..\Data\02Data';
[name, train_y] = getdataset(traindata);
[class, number] = size(name);
for i = 1:number
    img = rgb2gray(imread(name{1,i}));
    img = imresize(img, [32 32]);
    train_x(:, :, i) = double(img) / 255.0;
end

% load test dataset and labels
testdata = '..\..\..\..\..\..\Data\02Data';
[testname, test_y] = getdataset(testdata);
[class, number] = size(testname);
for i= 1:number
    img = rgb2gray(imread(testname{1, i}));
    img = imresize(img, [32 32]);
        
    test_x(:, :, i) = double(img) / 255.0;
end

%% ex1 
%will run 1 epoch in about 200 second and get around 11% error. 
%With 100 epochs you'll get around 1.2% error

cnn.layers = {
    struct('type', 'i') %input layer
    struct('type', 'c', 'outputmaps', 6, 'kernelsize', 5) %convolution layer
    struct('type', 's', 'scale', 2) %sub sampling layer
    struct('type', 'c', 'outputmaps', 12, 'kernelsize', 5) %convolution layer
    struct('type', 's', 'scale', 2) %subsampling layer
};
cnn = cnnsetup(cnn, train_x, train_y);

opts.alpha = 1;
opts.batchsize = 8;
opts.numepochs = 200;

cnn = cnntrain(cnn, train_x, train_y, opts);

[er, bad] = cnntest(cnn, test_x, test_y);

%plot mean squared error
plot(cnn.rL);
%show test error
disp([num2str(er*100) '% error']);