function [er, bad] = cnntest(net, x, y)
    %  feedforward
    net = cnnff(net, x);
    [temp, h] = max(net.o);
    [temp, a] = max(y);
    bad = find(h ~= a);

    % for test
    result = [a' h']
    % end
    
    er = numel(bad) / size(y, 2);
end
